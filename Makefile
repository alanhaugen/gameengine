.PHONY: release debug shaders

defualt: release

SHADERS = $(wildcard shaders/*.frag) $(wildcard shaders/*.vert) 

SPVS = $(SHADERS:%=%.spv)

shaders: $(SPVS)

%.vert.spv: %.vert
	glslangValidator -V -S vert $< -o $@

shaders/%.frag.spv: shaders/%.frag
	glslangValidator -V -S frag $< -o $@

PLATFORM = $(shell uname)

CC = clang++

LIBS = -lqt6 -lMoltenVK
INCLUDES = -I include

#$(wildcard source/*.cpp)

SRC = \
    source/modules/renderer/vulkan/vulkanrenderer.cpp \
    source/platforms/qt/mainwindow.cpp \
    source/main.cpp \
    source/platforms/application.cpp \
    source/platforms/qt/qtapplication.cpp \
    source/demos/vikingscene.cpp \
    source/components/mesh.cpp

OBJS = $(SOURCE:source/%.cpp=build/%.o)

LIB_DIRS = -L lib/$(PLATFORM)/arm64

ifeq ($(PLATFORM),Darwin) # macos
    INCLUDES += -I /opt/homebrew/opt/qt/include
    LIB_DIRS += -L /opt/homebrew/opt/qt/lib
endif

CFLAGS += $(INCLUDES) $(LIB_DIRS) $(LIBS)

release: $(OBJS) $(SPVS)
	$(CC) $(CFLAGS) $(OBJS) -o game

debub: $(OBJS) $(SPVS)
	$(CC) $(CFLAGS) -g $(OBJS) -o game

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
