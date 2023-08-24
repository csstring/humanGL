CXX = c++
# 컴파일 플래그
#CXXFLAGS = -Wall -Wextra -Werror
CXXFLAGS = -std=c++17
# 링크 플래그
LDFLAGS = 
# 소스코드 파일 경로
SRC_DIR = ./src
# 오브젝트 파일 경로
OBJ_DIR = ./obj
# 헤더 파일 경로
INC_DIR = ./include
# 라이브러리 파일 경로
LIB_DIR = ./lib-universal

# GLFW 라이브러리 파일 경로
GLFW_LIB_DIR = $(LIB_DIR)

# 바이너리 파일
TARGET = ./humanGL
# 소스 파일 리스트. Searching in src, src/Body, src/IK, and src/Animation
SOURCES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/Body/*.cpp $(SRC_DIR)/Math/*.cpp $(SRC_DIR)/IK/*.cpp $(SRC_DIR)/AnimationBlend/*.cpp)
# 오브젝트 파일 리스트
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/Math/%.cpp,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/Body/%.cpp,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/IK/%.cpp,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/AnimationBlend/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))))))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^ -L$(GLFW_LIB_DIR) -lglfw3 -lGLEW -lPhysX_static_64 -lPhysXCharacterKinematic_static_64 \
	-lPhysXCommon_static_64 -lPhysXCooking_static_64 -lPhysXExtensions_static_64 -lPhysXFoundation_static_64 \
	-lPhysXPvdSDK_static_64 -lPhysXVehicle_static_64 \
	-lSnippetRender_static_64 -lSnippetUtils_static_64 -framework Cocoa -framework OpenGL -framework IOKit

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -I$(INC_DIR)/physx -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/Body/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -I$(INC_DIR)/physx -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/IK/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -I$(INC_DIR)/physx -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/AnimationBlend/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -I$(INC_DIR)/physx -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/Math/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -I$(INC_DIR)/physx -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o

fclean: clean
	rm -f $(TARGET)

.PHONY: all clean fclean