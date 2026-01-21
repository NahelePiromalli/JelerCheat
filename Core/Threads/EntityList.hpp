#pragma once
#include <Includes/Includes.hpp>
#include <unordered_map>
#include <string>
#include <mutex>
#include <vector>

namespace Core {
    namespace Threads {

        class cEntityList {
        private:
            std::mutex EntityListMutex;
            std::unordered_map<CPed*, Core::SDK::Game::EntityStruct> CachedEntities;

        public:
            inline std::string getPlayerNameByNetId(int netid) {
                uintptr_t ModBase;
                uintptr_t playernames = Mem.GetModuleBaseAddr(g_Variables.ProcIdFiveM, "citizen-playernames-five.dll", &ModBase);
                uintptr_t PlayerNamesArray = Mem.Read<uintptr_t>(playernames + 0x30D38);
                int LastPlayer = Mem.Read<int>(playernames + 0x30D38 + 0x8);
                auto list = Mem.Read<uintptr_t>(PlayerNamesArray + 0x8);
                std::string name = "npc";

                for (int i = 0; i < LastPlayer; i++) {
                    int id = Mem.Read<int>(list + 0x10);
                    if (netid == id) {
                        name = Mem.ReadString(list + 0x18);
                        break;
                    }
                    list = Mem.Read<uintptr_t>(list + 8);
                }

                return name;
            }

            void Update() {
                while (true) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));

                    if (!g_MenuInfo.IsLogged && !g_Variables.g_bPassedByThisVerify)
                        continue;

                    if (!Core::SDK::Pointers::pReplayInterFace)
                        continue;

                    CPedInterFace* CPedInterFace = Core::SDK::Pointers::pReplayInterFace->InterfacePed();
                    CPedList* CPedList = CPedInterFace->PedList();

                    if (!CPedInterFace || !CPedList)
                        continue;

                    size_t Index = 0;
                    static const int PedCount = CPedInterFace->MaxPed();

                    {
                        std::lock_guard<std::mutex> Guard(EntityListMutex);

                        for (int i = 0; i < PedCount; i++) {
                            CPed* CurrentPed = CPedList->Ped(i);
                            if (!CurrentPed)
                                continue;

                            int PlayerId = CurrentPed->GetID();

                            if (CachedEntities.find(CurrentPed) == CachedEntities.end()) {
                                Core::SDK::Game::EntityStruct NewEntity;
                                NewEntity.Id = PlayerId;
                                NewEntity.Index = i;
                                NewEntity.Pos = CurrentPed->GetPos();
                                NewEntity.IsFriend = Core::SDK::Game::FriendMap[CurrentPed];
                                NewEntity.MaxHealth = CurrentPed->GetMaxHealth();
                                NewEntity.Health = CurrentPed->GetHealth();
                                NewEntity.Armor = CurrentPed->GetArmor();
                                NewEntity.PedType = CurrentPed->GetPedType();
                                NewEntity.Distance = CurrentPed->GetDistance(Core::SDK::Pointers::pLocalPlayer->GetPos(), NewEntity.Pos);

                                CachedEntities[CurrentPed] = NewEntity;
                            }

                            // Atualiza as informações dinâmicas da entidade
                            Core::SDK::Game::EntityStruct CachedEntity = CachedEntities[CurrentPed];
                            CachedEntity.Health = CurrentPed->GetHealth();
                            CachedEntity.Armor = CurrentPed->GetArmor();
                            CachedEntity.Pos = CurrentPed->GetPos();
                            CachedEntity.IsFriend = Core::SDK::Game::FriendMap[CurrentPed];
                            CachedEntity.Distance = CurrentPed->GetDistance(Core::SDK::Pointers::pLocalPlayer->GetPos(), CachedEntity.Pos);
                            CachedEntity.WeaponName = CurrentPed->GetWeaponManager()->GetWeaponInfo()->GetName();

                            Core::SDK::Game::EntityStruct Entity;
                            Entity.Ped = CurrentPed;
                            Entity.Id = CachedEntity.Id;
                            Entity.Index = CachedEntity.Index;
                            Entity.Pos = CachedEntity.Pos;
                            Entity.IsFriend = CachedEntity.IsFriend;
                            Entity.MaxHealth = CachedEntity.MaxHealth;
                            Entity.Health = CachedEntity.Health;
                            Entity.Armor = CachedEntity.Armor;
                            Entity.PedType = CachedEntity.PedType;
                            Entity.Distance = CachedEntity.Distance;
                            Entity.WeaponName = CachedEntity.WeaponName;

                            // Aqui usamos a função que lê o nome diretamente da memória
                            Entity.NetworkInfo.UserName = getPlayerNameByNetId(PlayerId);
                            Entity.NetworkInfo.SteamId = Core::Threads::g_UpdateNames.NetworkMap[PlayerId].SteamId;
                            Entity.NetworkInfo.DiscordId = Core::Threads::g_UpdateNames.NetworkMap[PlayerId].DiscordId;

                            if (Index < Core::SDK::Game::EntityList.size())
                                Core::SDK::Game::EntityList[Index] = Entity;
                            else
                                Core::SDK::Game::EntityList.push_back(Entity);

                            Index++;
                        }
                    }

                    if (Index < Core::SDK::Game::EntityList.size())
                        Core::SDK::Game::EntityList.resize(Index);
                }
            }
        };

        inline cEntityList g_EntityList;
    }
}
