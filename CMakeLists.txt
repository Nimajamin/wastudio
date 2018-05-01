cmake_minimum_required(VERSION 2.6)
project(WASTUDIO)

#set(PLANK_CPP src/plank.cpp)

set(GLUTEN_LIBS GLEW GL glut GLU)
set(WAVEFRONT_LIBS GLEW GL)

if(WIN32)
  set(GLUTEN_LIBS glew32 opengl32 glu32 freeglut)
  set(WAVEFRONT_LIBS glew32 opengl32)

  if(MINGW)
    set(PLATFORM_INCLUDE_DIRECTORIES
      ${PROJECT_SOURCE_DIR}/contrib/windows/mingw/glew/include
      ${PROJECT_SOURCE_DIR}/contrib/windows/mingw/freeglut/include
    )
    set(PLATFORM_LINK_DIRECTORIES
      ${PROJECT_SOURCE_DIR}/contrib/windows/mingw/glew/lib
      ${PROJECT_SOURCE_DIR}/contrib/windows/mingw/freeglut/lib
    )
  elseif(MSVC)
    set(PLATFORM_INCLUDE_DIRECTORIES
      ${PROJECT_SOURCE_DIR}/contrib/windows/msvc/dirent/include
      ${PROJECT_SOURCE_DIR}/contrib/windows/msvc/glew/include
      ${PROJECT_SOURCE_DIR}/contrib/windows/msvc/freeglut/include
    )
    set(PLATFORM_LINK_DIRECTORIES
      ${PROJECT_SOURCE_DIR}/contrib/windows/msvc/glew/lib
      ${PROJECT_SOURCE_DIR}/contrib/windows/msvc/freeglut/lib
    )
  endif()
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  set(PLATFORM_INCLUDE_DIRECTORIES
    /usr/local/include
    /usr/X11R6/include
  )
  set(PLATFORM_LINK_DIRECTORIES
    /usr/local/lib
    /usr/X11R6/lib
  )
endif()

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src/gluten/include
  ${PLATFORM_INCLUDE_DIRECTORIES}
)

link_directories(
  ${PLATFORM_LINK_DIRECTORIES}
)

add_library(gluten
  src/gluten/Panel.cpp
  src/gluten/Component.cpp
  src/gluten/Rectangle.cpp
  src/gluten/Font.cpp
  src/gluten/HScroll.cpp
  src/gluten/Window.cpp
  src/gluten/Button.cpp
  src/gluten/SaveFileDialog.cpp
  src/gluten/Color.cpp
  src/gluten/ImageButton.cpp
  src/gluten/Label.cpp
  src/gluten/OpenFileDialog.cpp
  src/gluten/Image.cpp
  src/gluten/ListBox.cpp
  src/gluten/PictureBox.cpp
  src/gluten/Png.cpp
  src/gluten/CheckBox.cpp
  src/gluten/Resource.cpp
  src/gluten/Core.cpp
  src/gluten/Mouse.cpp
  src/gluten/PopupMenu.cpp
  src/gluten/Path.cpp
  src/gluten/MessageBox.cpp
  src/gluten/TextBox.cpp
  src/gluten/lodepng.cpp
)

target_link_libraries(gluten ${GLUTEN_LIBS})

add_library(wavefront
  src/wavefront/Face.cpp
  src/wavefront/Material.cpp
  src/wavefront/Translation.cpp
  src/wavefront/Animation.cpp
  src/wavefront/Model.cpp
  src/wavefront/Texture.cpp
  src/wavefront/TriBoxCollision.cpp
  src/wavefront/Part.cpp
  src/wavefront/Frame.cpp
  src/wavefront/MaterialGroup.cpp
  src/wavefront/Vertex.cpp
  src/wavefront/lodepng.cpp
)

target_link_libraries(wavefront ${WAVEFRONT_LIBS})

add_executable(wastudio
  ${PLANK_CPP}
  src/wastudio/AboutWindow.cpp
  src/wastudio/IntroWindow.cpp
  src/wastudio/ModelWindow.cpp
  src/wastudio/RenameWindow.cpp
  src/wastudio/TestWindow.cpp
  src/wastudio/TutorialWindow.cpp
  src/wastudio/main.cpp
)

target_link_libraries(wastudio wavefront gluten)
