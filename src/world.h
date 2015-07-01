// Copyright 2015 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ZOOSHI_WORLD_H_
#define ZOOSHI_WORLD_H_

#include <map>
#include <string>
#include "components_generated.h"
#include "components/attributes.h"
#include "components/audio_listener.h"
#include "components/editor.h"
#include "components/patron.h"
#include "components/physics.h"
#include "components/player.h"
#include "components/player_projectile.h"
#include "components/rail_denizen.h"
#include "components/rendermesh.h"
#include "components/river.h"
#include "components/sound.h"
#include "components/services.h"
#include "components/shadow_controller.h"
#include "components/time_limit.h"
#include "components/transform.h"
#include "editor/world_editor.h"
#include "entity/entity_manager.h"
#include "motive/engine.h"
#include "railmanager.h"
#include "zooshi_entity_factory.h"

#ifdef USING_GOOGLE_PLAY_GAMES
#include "gpg_manager.h"
#include "gpg_multiplayer.h"
#endif

namespace pindrop {

class AudioEngine;

}  // namespace pindrop

namespace fpl {

class InputSystem;
class AssetManager;

namespace fpl_project {

struct Config;
class BasePlayerController;

class World {
 public:
  World()
    :   is_in_cardboard(false),
        draw_debug_physics(false) {}

  void Initialize(const Config& config, InputSystem* input_system,
                  BasePlayerController* input_controller,
                  AssetManager* asset_manager, FontManager* font_manager,
                  pindrop::AudioEngine* audio_engine,
                  event::EventManager* event_manager);

  bool LoadEntitiesFromFile(const char* entity_list_filename);
  motive::MotiveEngine motive_engine;

  // Entity manager
  entity::EntityManager entity_manager;

  // Entity factory, for creating entities from data.
  ZooshiEntityFactory entity_factory;

  // Rail Manager - manages loading and storing of rail definitions
  RailManager rail_manager;

  // Components
  TransformComponent transform_component;
  RailDenizenComponent rail_denizen_component;
  PlayerComponent player_component;
  PlayerProjectileComponent player_projectile_component;
  RenderMeshComponent render_mesh_component;
  PhysicsComponent physics_component;
  PatronComponent patron_component;
  TimeLimitComponent time_limit_component;
  AudioListenerComponent audio_listener_component;
  SoundComponent sound_component;
  AttributesComponent attributes_component;
  RiverComponent river_component;
  ServicesComponent services_component;
  ShadowControllerComponent shadow_controller_component;
  EditorComponent editor_component_;

  // Each player has direct control over one entity.
  entity::EntityRef active_player_entity;

  const Config* config;

  AssetManager* asset_manager;

  // TODO: Refactor all components so they don't require their source
  // data to remain in memory after their initial load. Then get rid of this,
  // which keeps all entity files loaded in memory.
  std::map<std::string, std::string> loaded_entity_files_;

  // Determines if the game is in Cardboard mode (for special rendering)
  bool is_in_cardboard;

  // Determines if the debug drawing of physics should be used
  bool draw_debug_physics;

#ifdef USING_GOOGLE_PLAY_GAMES
  GPGManager* gpg_manager;

  // Network multiplayer library for multi-screen version
  GPGMultiplayer* gpg_multiplayer;
#endif
};

}  // fpl_project
}  // fpl

#endif  // ZOOSHI_WORLD_H_