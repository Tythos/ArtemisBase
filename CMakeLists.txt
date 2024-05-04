cmake_minimum_required(VERSION 3.14)
project(ArtemisBase)

# define library contents
add_library(${PROJECT_NAME} STATIC
    "App.cpp"
    "Camera.cpp"
    "Color.cpp"
    "Event.cpp"
    "EventList.cpp"
    "Graphics.cpp"
    "Keyboard.cpp"
    "Light.cpp"
    "Mesh.cpp"
    "Model.cpp"
    "Object.cpp"
    "Panel.cpp"
    #"Skybox.cpp"
    #"Stopwatch.cpp"
    #"TexCoord.cpp"
    "Vertex.cpp"
)

# add ArtemisUtility dependency
add_subdirectory("ArtemisUtility/" EXCLUDE_FROM_ALL)
target_include_directories(${PROJECT_NAME} PRIVATE "ArtemisUtility/")

# add glew dependency
add_subdirectory("glew-cmake/" EXCLUDE_FROM_ALL)
target_include_directories(${PROJECT_NAME} PRIVATE "glew-cmake/include")

# add KirkMath dependency
add_subdirectory("KirkMath/" EXCLUDE_FROM_ALL)
target_include_directories(${PROJECT_NAME} PRIVATE "KirkMath/")

# add SDL dependency
add_subdirectory("SDL/" EXCLUDE_FROM_ALL)
target_include_directories(${PROJECT_NAME} PRIVATE "SDL/include")

# add SDL_ttf dependency
add_subdirectory("SDL_ttf/" EXCLUDE_FROM_ALL)
target_include_directories(${PROJECT_NAME} PRIVATE "SDL_ttf/")

# add SDL_image dependency
add_subdirectory("SDL_image/" EXCLUDE_FROM_ALL)
target_include_directories(${PROJECT_NAME} PRIVATE "SDL_image/include")
