# CMakeList.txt : projet CMake pour Babel, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(NOT CMAKE_C_COMPILE_OBJECT)
  set(CMAKE_C_COMPILE_OBJECT
    "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>")
endif()

if (MSVC)
    set(CROSS_COMPILE_FILE
        DLLoader/window_load.c
        FileSystemWatcher/windows_get_current_path.c)
else()
    set(CROSS_COMPILE_FILE
        DLLoader/linux_load.c
        FileSystemWatcher/linux_get_current_path.c)

    set(CROSS_COMPILE_LIB
        "${CMAKE_DL_LIBS}"
    )
endif()

add_library(common_library STATIC
    # Engine
    Engine/Entity.cpp
    Engine/Entity.hpp
    Engine/IEntity.hpp
    Engine/Component.cpp
    Engine/Component.hpp
    Engine/IComponent.hpp
    Engine/System.cpp
    Engine/System.hpp
    Engine/ISystem.hpp

    Engine/EntitySignature.cpp
    Engine/EntitySignature.hpp

    Engine/ComponentArray.hpp
    Engine/IComponentArray.hpp
    
    Engine/EntityIdFactory.cpp
    Engine/EntityIdFactory.hpp
    Engine/IEntityIdFactory.hpp
    Engine/ComponentFactory.cpp
    Engine/ComponentFactory.hpp
    Engine/IComponentFactory.hpp
    Engine/SystemFactory.cpp
    Engine/SystemFactory.hpp

    Engine/REngine.cpp
    Engine/REngine.hpp
    Engine/IREngine.hpp
    
    # Engine User Usage
    Engine/REntity.cpp
    Engine/REntity.hpp
    Engine/RComponent.cpp
    Engine/RComponent.hpp
    Engine/RSystem.cpp
    Engine/RSystem.hpp

    # Entities, Components and Systems
    Entities/ExampleEntity.hpp
    Entities/ExampleEntity.cpp
    Entities/UI/UI.hpp
    Entities/UI/UI.cpp
    Entities/UI/UIImage/UIImage.hpp
    Entities/UI/UIImage/UIImage.cpp
    Entities/UI/UIText/UIText.hpp
    Entities/UI/UIText/UIText.cpp
    Entities/UI/UIButton/UIButton.hpp
    Entities/UI/UIButton/UIButton.cpp
    Entities/Object/Obstacle/Obstacle.hpp
    Entities/Object/Obstacle/Obstacle.cpp
    Entities/Object/Character/NonPlayerCharacter/NPC.hpp
    Entities/Object/Character/NonPlayerCharacter/NPC.cpp
    Entities/Object/Character/NonPlayerCharacter/Ally/Ally.hpp
    Entities/Object/Character/NonPlayerCharacter/Ally/Ally.cpp
    Entities/Object/Character/NonPlayerCharacter/Enemy/Enemy.hpp
    Entities/Object/Character/NonPlayerCharacter/Enemy/Enemy.cpp
    Entities/Object/Character/Character.hpp
    Entities/Object/Character/Character.cpp
    Entities/Object/Character/Player/Player.hpp
    Entities/Object/Character/Player/Player.cpp
    Entities/Object/Object.hpp
    Entities/Object/Object.cpp
    Entities/Object/Particle/Particle.hpp
    Entities/Object/Particle/Particle.cpp
    Entities/Object/Particle/Bullet/Bullet.hpp
    Entities/Object/Particle/Bullet/Bullet.cpp
    Entities/Object/Pickable/Pickable.hpp
    Entities/Object/Pickable/Pickable.cpp
    Entities/UI/UITextInput/UITextInput.hpp
    Entities/UI/UITextInput/UITextInput.cpp
    Entities/MusicPlayer/MusicPlayer.hpp
    Entities/MusicPlayer/MusicPlayer.cpp

    Components/ExampleComponent.hpp
    Components/ExampleComponent.cpp
    Components/Transform/Transform.hpp
    Components/Transform/Transform.cpp
    Components/UITransform/UITransform.hpp
    Components/UITransform/UITransform.cpp
    Components/KeyInput/KeyInput.hpp
    Components/KeyInput/KeyInput.cpp
    Components/CharacterCharacteristics/Weapon/Weapon.hpp
    Components/CharacterCharacteristics/Weapon/Weapon.cpp
    Components/CharacterCharacteristics/CharacterCharacteristics.hpp
    Components/CharacterCharacteristics/CharacterCharacteristics.cpp
    Components/Collider/Collider.cpp
    Components/Collider/Collider.hpp
    Components/Collider/CircleCollider/CircleCollider.cpp
    Components/Collider/CircleCollider/CircleCollider.hpp
    Components/Collider/RectangleCollider/RectangleCollider.cpp
    Components/Collider/RectangleCollider/RectangleCollider.hpp
    Components/Text/Text.cpp
    Components/Text/Text.hpp
    Components/Audio/Audio.hpp
    Components/Audio/Audio.cpp
    Components/Button/Button.hpp
    Components/Button/Button.cpp
    Components/Sprite/Sprite.cpp
    Components/Sprite/Sprite.hpp
    Components/Sprite/Animation/SpriteAnimation.cpp
    Components/Sprite/Animation/SpriteAnimation.hpp
    Components/TextInput/TextInput.hpp
    Components/TextInput/TextInput.cpp

    Systems/ExampleSystem.hpp
    Systems/ExampleSystem.cpp
    Systems/ColliderSystem.hpp
    Systems/ColliderSystem.cpp
    Systems/MovementSystem.hpp
    Systems/MovementSystem.cpp
    Systems/InputSystem.hpp
    Systems/InputSystem.cpp
    Systems/RenderingSystem.hpp
    Systems/RenderingSystem.cpp
    Systems/RenderingSystem/DrawableContainer.hpp

    # DLLoader
    DLLoader/DLLoader.cpp
    DLLoader/DLLoader.hpp
    DLLoader/RTypeDLLoader.cpp
    DLLoader/RTypeDLLoader.hpp
    "${CROSS_COMPILE_FILE}"

    #FileSystemWatcher
    FileSystemWatcher/RTypeFileSystemWatcher.cpp
    FileSystemWatcher/RTypeFileSystemWatcher.hpp
    FileSystemWatcher/Chrono.cpp
    FileSystemWatcher/Chrono.hpp

    DebugController.cpp
    DebugController.hpp
    Chronometer.cpp
    Chronometer.hpp

    Engine/NetworkEngine.cpp
    Engine/NetworkEngine.hpp
)

target_link_libraries(common_library PUBLIC
    "${CROSS_COMPILE_LIB}"
    "${CONAN_LIBS}"
    #CONAN_PKG::sfml
)

target_include_directories(common_library PUBLIC
    "${CONAN_INCLUDE_DIRS_SFML}"
)

add_subdirectory(Game)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
