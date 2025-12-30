# =============================================================================
# ZYK Data Structures in C - Makefile
# =============================================================================
# 使用方法 / Usage:
#   make          - 构建项目
#   make clean    - 清理构建产物
#   make rebuild  - 完全重建
#   make run      - 构建并运行
# =============================================================================

# 编译器与标准
CC      = cc
CFLAGS  = -std=c99 -Wall -Wextra -pedantic
LDFLAGS =

# 目录结构
SRC_DIR   = src
INC_DIR   = include/dsc
BUILD_DIR = build

# 头文件搜索路径
INCLUDES = -I$(INC_DIR)

# 目标可执行文件
TARGET = $(BUILD_DIR)/ZYK_Data_Structures_In_C

# =============================================================================
# 源文件列表
# =============================================================================

# 基础工具库
WARN_SRC = $(SRC_DIR)/Warn.c

# 数据结构模块
DS_MODULES = SeqList LinkedList SeqStack LinkedStack \
             SeqQueue LinkedQueue SeqBinaryTree LinkedBinaryTree Sort

DS_SRCS = $(foreach mod,$(DS_MODULES),$(SRC_DIR)/$(mod).c)

# 主程序
MAIN_SRC = main.c

# 所有源文件
ALL_SRCS = $(WARN_SRC) $(DS_SRCS) $(MAIN_SRC)

# 目标文件（.o）
ALL_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(ALL_SRCS)))

# =============================================================================
# 构建规则
# =============================================================================

# 默认目标
all: $(TARGET)

# 链接生成可执行文件
$(TARGET): $(ALL_OBJS) | $(BUILD_DIR)
	@echo "🔗 Linking → $@"
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "✅ Build complete!"

# 编译 src/ 下的 .c 文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "🔨 Compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 编译 main.c（在根目录）
$(BUILD_DIR)/main.o: main.c | $(BUILD_DIR)
	@echo "🔨 Compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 创建构建目录
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# =============================================================================
# 便捷命令
# =============================================================================

# 运行程序
run: $(TARGET)
	@echo "🚀 Running..."
	@echo "----------------------------------------"
	@./$(TARGET)

# 清理构建产物
clean:
	@echo "🧹 Cleaning..."
	@rm -rf $(BUILD_DIR)
	@echo "✅ Clean complete!"

# 完全重建
rebuild: clean all

# 显示帮助
help:
	@echo "Available targets:"
	@echo "  make          - Build the project"
	@echo "  make run      - Build and run"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make help     - Show this help"

# 伪目标声明
.PHONY: all run clean rebuild help
