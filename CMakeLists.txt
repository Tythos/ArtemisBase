cmake_minimum_required(VERSION 3.14)
project(ArtemisBase)
add_subdirectory("SDL/" EXCLUDE_FROM_ALL)
add_library(${PROJECT_NAME} STATIC
    "App.cpp"
    "Camera.cpp"
    "Event.cpp"
    "EventList.cpp"
    "Graphics.cpp"
    #"Keyboard.cpp"
    #"Light.cpp"
    #"Mesh.cpp"
    #"Model.cpp"
    #"Object.cpp"
    #"Panel.cpp"
    #"Skybox.cpp"
    #"Stopwatch.cpp"
    #"TexCoord.cpp"
    #"Vertex.cpp"
)
