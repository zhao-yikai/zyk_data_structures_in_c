/*
 * ╔═══════════════════════════════════════════════════════════════════════════╗
 * ║                    THE MATRIX - DATA STRUCTURE EDITION                     ║
 * ║                     "Wake up, Neo... Follow the code"                      ║
 * ╚═══════════════════════════════════════════════════════════════════════════╝
 *
 * 一个融合所有数据结构的黑客帝国风格演示程序
 * Created By YikaiSays - Dec 30 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/* 数据结构头文件 */
#include "Common.h"
#include "SeqList.h"
#include "LinkedList.h"
#include "SeqStack.h"
#include "LinkedStack.h"
#include "SeqQueue.h"
#include "LinkedQueue.h"
#include "SeqBinaryTree.h"
#include "Sort.h"

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                               ANSI 颜色定义                                  */
/* ═══════════════════════════════════════════════════════════════════════════ */

#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define BLINK       "\033[5m"

/* Matrix 经典绿色系 */
#define GREEN       "\033[32m"
#define BRIGHT_GREEN "\033[92m"
#define DARK_GREEN  "\033[32;2m"

/* 其他颜色 */
#define RED         "\033[91m"
#define YELLOW      "\033[93m"
#define CYAN        "\033[96m"
#define WHITE       "\033[97m"
#define MAGENTA     "\033[95m"

/* 背景色 */
#define BG_BLACK    "\033[40m"

/* Matrix 风格组合 */
#define MATRIX_GREEN    BOLD GREEN
#define MATRIX_BRIGHT   BOLD BRIGHT_GREEN
#define MATRIX_DIM      DIM GREEN
#define MATRIX_GLOW     BOLD BRIGHT_GREEN BG_BLACK

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                               全局配置                                       */
/* ═══════════════════════════════════════════════════════════════════════════ */

#define MATRIX_WIDTH        80
#define MATRIX_HEIGHT       20
#define RAIN_DROPS          15
#define ANIMATION_FRAMES    30
#define DELAY_US            50000

/* Matrix 字符集 (保留供未来扩展) */
// static const char *MATRIX_CHARS = "ｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾙﾚﾛﾜﾝ0123456789";
// static const char *CODE_SYMBOLS = "{}[]()<>+-*/=&|^~!@#$%";

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                               数据结构节点                                    */
/* ═══════════════════════════════════════════════════════════════════════════ */

/* 雨滴结构 - 用于存储Matrix雨滴状态 */
typedef struct {
    int x;
    int y;
    int speed;
    int length;
    char trail[MATRIX_HEIGHT + 1];
} MatrixDrop;

/* 任务结构 - 用于模拟系统任务 */
typedef struct {
    int id;
    int priority;
    const char *name;
    double progress;
} SystemTask;

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                               工具函数                                        */
/* ═══════════════════════════════════════════════════════════════════════════ */

static void clear_screen(void) {
    printf("\033[2J\033[H");
}

static void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

static void hide_cursor(void) {
    printf("\033[?25l");
}

static void show_cursor(void) {
    printf("\033[?25h");
}

static void delay_ms(int ms) {
    usleep(ms * 1000);
}

static char random_matrix_char(void) {
    const char simple_chars[] = "01@#$%&*+-=<>[]{}|/\\~";
    return simple_chars[rand() % (sizeof(simple_chars) - 1)];
}

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                            ASCII 艺术                                        */
/* ═══════════════════════════════════════════════════════════════════════════ */

static void print_matrix_logo(void) {
    printf(MATRIX_BRIGHT);
    printf("\n");
    printf("  ████████╗██╗  ██╗███████╗    ███╗   ███╗ █████╗ ████████╗██████╗ ██╗██╗  ██╗\n");
    printf("  ╚══██╔══╝██║  ██║██╔════╝    ████╗ ████║██╔══██╗╚══██╔══╝██╔══██╗██║╚██╗██╔╝\n");
    printf("     ██║   ███████║█████╗      ██╔████╔██║███████║   ██║   ██████╔╝██║ ╚███╔╝ \n");
    printf("     ██║   ██╔══██║██╔══╝      ██║╚██╔╝██║██╔══██║   ██║   ██╔══██╗██║ ██╔██╗ \n");
    printf("     ██║   ██║  ██║███████╗    ██║ ╚═╝ ██║██║  ██║   ██║   ██║  ██║██║██╔╝ ██╗\n");
    printf("     ╚═╝   ╚═╝  ╚═╝╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝\n");
    printf(RESET);
    printf(MATRIX_DIM);
    printf("\n            ╔════════════════════════════════════════════════════╗\n");
    printf("            ║   D A T A   S T R U C T U R E   E D I T I O N      ║\n");
    printf("            ╚════════════════════════════════════════════════════╝\n\n");
    printf(RESET);
}

static void print_separator(const char *title) {
    printf(MATRIX_GREEN);
    printf("\n╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ " MATRIX_BRIGHT "%-73s" MATRIX_GREEN " ║\n", title);
    printf("╚═══════════════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}

static void print_mini_separator(void) {
    printf(MATRIX_DIM "────────────────────────────────────────────────────────────────────────────\n" RESET);
}

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                            MATRIX 数字雨动画                                  */
/* ═══════════════════════════════════════════════════════════════════════════ */

static void matrix_rain_animation(int frames) {
    MatrixDrop drops[RAIN_DROPS];
    char screen[MATRIX_HEIGHT][MATRIX_WIDTH + 1];

    /* 使用 SeqQueue 存储历史帧数据 */
    SeqQueue frameHistory = SeqQueue_Create(10);

    /* 初始化雨滴 */
    for (int i = 0; i < RAIN_DROPS; i++) {
        drops[i].x = rand() % MATRIX_WIDTH;
        drops[i].y = rand() % MATRIX_HEIGHT - MATRIX_HEIGHT;
        drops[i].speed = 1 + rand() % 3;
        drops[i].length = 3 + rand() % 8;
    }

    hide_cursor();

    for (int frame = 0; frame < frames; frame++) {
        /* 清空屏幕缓冲 */
        memset(screen, ' ', sizeof(screen));
        for (int y = 0; y < MATRIX_HEIGHT; y++) {
            screen[y][MATRIX_WIDTH] = '\0';
        }

        /* 更新并绘制雨滴 */
        for (int i = 0; i < RAIN_DROPS; i++) {
            drops[i].y += drops[i].speed;

            if (drops[i].y > MATRIX_HEIGHT + drops[i].length) {
                drops[i].x = rand() % MATRIX_WIDTH;
                drops[i].y = -drops[i].length;
                drops[i].speed = 1 + rand() % 3;
            }

            /* 绘制雨滴轨迹 */
            for (int j = 0; j < drops[i].length; j++) {
                int y = drops[i].y - j;
                if (y >= 0 && y < MATRIX_HEIGHT && drops[i].x < MATRIX_WIDTH) {
                    screen[y][drops[i].x] = random_matrix_char();
                }
            }
        }

        /* 渲染屏幕 */
        move_cursor(1, 1);
        for (int y = 0; y < MATRIX_HEIGHT; y++) {
            for (int x = 0; x < MATRIX_WIDTH; x++) {
                if (screen[y][x] != ' ') {
                    /* 头部最亮，尾部渐暗 */
                    int is_head = 0;
                    for (int i = 0; i < RAIN_DROPS; i++) {
                        if (drops[i].x == x && drops[i].y == y) {
                            is_head = 1;
                            break;
                        }
                    }
                    if (is_head) {
                        printf(MATRIX_BRIGHT "%c" RESET, screen[y][x]);
                    } else {
                        printf(MATRIX_GREEN "%c" RESET, screen[y][x]);
                    }
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }

        /* 使用队列记录帧号 */
        if (!SeqQueue_IsFull(frameHistory)) {
            SeqQueue_Enqueue(frameHistory, (ElementType)frame);
        }

        delay_ms(80);
    }

    /* 清理 */
    SeqQueue_Destroy(frameHistory);
    show_cursor();
    clear_screen();
}

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                         DEMO 1: 顺序表 - 系统初始化                           */
/* ═══════════════════════════════════════════════════════════════════════════ */

static void demo_seqlist_system_init(void) {
    print_separator("SYSTEM INITIALIZATION :: SeqList Module Loading");

    SeqList sysModules = SeqList_Create();

    const char *modules[] = {
        "KERNEL_CORE", "MEMORY_MANAGER", "PROCESS_SCHEDULER",
        "FILE_SYSTEM", "NETWORK_STACK", "SECURITY_LAYER",
        "DATA_ANALYZER", "NEURAL_INTERFACE"
    };
    int module_count = sizeof(modules) / sizeof(modules[0]);

    printf(MATRIX_GREEN "\n  [SYSTEM] Loading core modules into sequential memory...\n\n" RESET);

    for (int i = 0; i < module_count; i++) {
        SeqList_InsertAt(sysModules, (ElementType)(i + 1) * 100, i);

        printf("  " MATRIX_DIM "[" MATRIX_BRIGHT "%02d" MATRIX_DIM "]" RESET, i);
        printf(" Loading " MATRIX_GREEN "%-20s" RESET, modules[i]);

        /* 进度条动画 */
        printf(" [");
        for (int j = 0; j <= 20; j++) {
            printf(MATRIX_BRIGHT "█" RESET);
            fflush(stdout);
            delay_ms(15);
        }
        printf("] " MATRIX_BRIGHT "OK" RESET);
        printf("  addr: " CYAN "0x%04X\n" RESET, (int)SeqList_GetElementAt(sysModules, i));
    }

    printf(MATRIX_GREEN "\n  [SYSTEM] Total modules loaded: %d\n" RESET, SeqList_GetLength(sysModules));
    printf(MATRIX_GREEN "  [SYSTEM] Memory status: " MATRIX_BRIGHT "OPTIMAL\n" RESET);

    /* 测试查找功能 */
    printf("\n  " MATRIX_DIM "Verifying module integrity..." RESET);
    SeqPosition pos = SeqList_Find(sysModules, 500.0);
    if (pos >= 0) {
        printf(MATRIX_GREEN " MODULE_500 found at position %d\n" RESET, pos);
    }

    print_mini_separator();
}

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                         DEMO 2: 链表 - 网络节点追踪                           */
/* ═══════════════════════════════════════════════════════════════════════════ */

static void demo_linkedlist_network_trace(void) {
    print_separator("NETWORK TRACE :: LinkedList Node Tracking");

    LinkedListHead networkNodes = LinkedList_Create();

    printf(MATRIX_GREEN "\n  [TRACE] Scanning network topology...\n\n" RESET);

    /* 模拟网络IP地址 (用整数表示) */
    double ip_parts[] = {192168001001, 192168001002, 10000000001,
                         172016000001, 192168002100, 10000000255};
    int ip_count = sizeof(ip_parts) / sizeof(ip_parts[0]);

    for (int i = 0; i < ip_count; i++) {
        LinkedList_InsertAtNodePosition(networkNodes, ip_parts[i], i + 1);

        printf("  " MATRIX_DIM "├──" MATRIX_GREEN " Node #%d " RESET, i + 1);
        printf(CYAN "IP: ");

        /* 打印动画效果 */
        long long ip = (long long)ip_parts[i];
        printf("%03lld.%03lld.%03lld.%03lld",
               (ip / 1000000000) % 1000,
               (ip / 1000000) % 1000,
               (ip / 1000) % 1000,
               ip % 1000);
        printf(RESET);

        printf(" " MATRIX_GREEN "[CONNECTED]" RESET "\n");
        delay_ms(150);
    }

    printf("  " MATRIX_DIM "└──" MATRIX_GREEN " End of trace\n" RESET);
    printf(MATRIX_GREEN "\n  [TRACE] Active nodes: %lld\n" RESET,
           (long long)LinkedList_GetLength(networkNodes));

    /* 查找特定节点 */
    printf("\n  " MATRIX_DIM "Searching for gateway node..." RESET);
    LinkedList_Position found = LinkedList_Find(networkNodes, 192168001001);
    if (found != NULL) {
        printf(MATRIX_BRIGHT " FOUND!\n" RESET);
    }

    LinkedList_Destroy(networkNodes);
    print_mini_separator();
}

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                         DEMO 3: 栈 - 系统调用追踪                             */
/* ═══════════════════════════════════════════════════════════════════════════ */

static void demo_stack_call_trace(void) {
    print_separator("CALL STACK TRACE :: Stack Operations");

    /* 使用顺序栈 */
    SeqStack callStack = SeqStack_Create(20);
    /* 使用链式栈 */
    LinkedStackHead backupStack = LinkedStack_Create();

    const char *functions[] = {
        "main()", "system_init()", "connect_matrix()",
        "load_neural_net()", "decrypt_signal()",
        "process_data()", "transmit_packet()"
    };
    int func_count = sizeof(functions) / sizeof(functions[0]);

    printf(MATRIX_GREEN "\n  [STACK] Simulating deep system call trace...\n\n" RESET);
    printf("  " MATRIX_DIM "╔═══════════════════════════════════════════════════╗\n");
    printf("  ║" RESET "             CALL STACK VISUALIZATION              " MATRIX_DIM "║\n");
    printf("  ╚═══════════════════════════════════════════════════╝\n" RESET);

    /* PUSH 操作 */
    printf("\n  " MATRIX_BRIGHT ">>> PUSHING STACK FRAMES <<<\n\n" RESET);

    for (int i = 0; i < func_count; i++) {
        SeqStack_Push(callStack, (ElementType)(i + 1) * 0x1000);
        LinkedStack_Push(backupStack, (ElementType)(i + 1));

        printf("  ");
        for (int j = 0; j < i; j++) printf("  ");
        printf(MATRIX_GREEN "┌───────────────────────────┐\n" RESET);
        printf("  ");
        for (int j = 0; j < i; j++) printf("  ");
        printf(MATRIX_GREEN "│ " MATRIX_BRIGHT "%-25s" MATRIX_GREEN " │ "
               CYAN "RSP: 0x%04X\n" RESET,
               functions[i], (i + 1) * 0x1000);

        delay_ms(200);
    }

    printf(MATRIX_GREEN "\n  [STACK] Stack depth: %d frames\n" RESET, func_count);

    /* POP 操作 */
    printf("\n  " MATRIX_BRIGHT ">>> UNWINDING STACK <<<\n\n" RESET);

    while (!SeqStack_isEmpty(callStack)) {
        ElementType frame = SeqStack_Pop(callStack);
        printf("  " MATRIX_DIM "POP " MATRIX_GREEN "→ " RESET);
        printf("Frame " CYAN "0x%04X" RESET " returned\n", (int)frame);
        delay_ms(100);
    }

    printf(MATRIX_GREEN "\n  [STACK] All frames unwound. Stack empty: %s\n" RESET,
           SeqStack_isEmpty(callStack) ? "TRUE" : "FALSE");

    LinkedStack_Delete(backupStack);
    print_mini_separator();
}

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                         DEMO 4: 队列 - 消息队列处理                           */
/* ═══════════════════════════════════════════════════════════════════════════ */

static void demo_queue_message_processing(void) {
    print_separator("MESSAGE QUEUE :: Queue-Based Processing");

    SeqQueue msgQueue = SeqQueue_Create(15);
    LinkedQueue priorityQueue = LinkedQueue_Create();

    printf(MATRIX_GREEN "\n  [QUEUE] Initializing message processing system...\n\n" RESET);

    /* 入队消息 */
    const char *messages[] = {
        "SYSTEM_ALERT", "DATA_PACKET", "AUTH_REQUEST",
        "HEARTBEAT", "SYNC_SIGNAL", "ENCRYPT_CMD",
        "DECODE_MSG", "TRANSMIT_ACK"
    };
    int msg_count = sizeof(messages) / sizeof(messages[0]);

    printf("  " MATRIX_DIM "╔═══════════════════════════════════════════════════╗\n");
    printf("  ║" MATRIX_BRIGHT "              INCOMING MESSAGE QUEUE               " MATRIX_DIM "║\n");
    printf("  ╚═══════════════════════════════════════════════════╝\n" RESET);

    for (int i = 0; i < msg_count; i++) {
        SeqQueue_Enqueue(msgQueue, (ElementType)(1000 + i));
        LinkedQueue_Enqueue(priorityQueue, (ElementType)(i % 3 + 1));

        printf("\n  " MATRIX_GREEN "ENQUEUE " RESET "→ ");
        printf(CYAN "MSG_%04d" RESET " : ", 1000 + i);
        printf(YELLOW "%-15s" RESET, messages[i]);
        printf(" [Priority: " MAGENTA "%d" RESET "]", (i % 3) + 1);

        /* 模拟队列可视化 */
        printf("\n  " MATRIX_DIM "Queue: [");
        for (int j = 0; j <= i && j < 8; j++) {
            if (j == i) printf(MATRIX_BRIGHT);
            printf("█");
            if (j == i) printf(MATRIX_DIM);
        }
        printf("]" RESET);

        delay_ms(150);
    }

    /* 出队处理 */
    printf("\n\n  " MATRIX_BRIGHT ">>> PROCESSING MESSAGES <<<\n" RESET);

    int processed = 0;
    while (!SeqQueue_IsEmpty(msgQueue)) {
        ElementType msg = SeqQueue_Dequeue(msgQueue);
        processed++;

        printf("\n  " MATRIX_GREEN "DEQUEUE " RESET "← ");
        printf(CYAN "MSG_%04d" RESET " ", (int)msg);

        /* 处理动画 */
        printf("[");
        for (int j = 0; j < 10; j++) {
            printf(MATRIX_BRIGHT "▓" RESET);
            fflush(stdout);
            delay_ms(30);
        }
        printf("] " MATRIX_GREEN "PROCESSED" RESET);
    }

    printf(MATRIX_GREEN "\n\n  [QUEUE] Total messages processed: %d\n" RESET, processed);

    SeqQueue_Destroy(msgQueue);
    print_mini_separator();
}

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                         DEMO 5: 二叉树 - 决策树                               */
/* ═══════════════════════════════════════════════════════════════════════════ */

static void demo_binary_tree_decision(void) {
    print_separator("DECISION TREE :: Binary Tree Analysis");

    printf(MATRIX_GREEN "\n  [TREE] Constructing neural decision pathway...\n\n" RESET);

    /* 手绘决策树可视化 */
    printf(MATRIX_BRIGHT);
    printf("                            ┌─────────────┐\n");
    printf("                            │" CYAN " ROOT: 100 " MATRIX_BRIGHT "│\n");
    printf("                            └──────┬──────┘\n");
    printf("                    ┌──────────────┴──────────────┐\n");
    printf("              ┌─────┴─────┐                 ┌─────┴─────┐\n");
    printf("              │" GREEN " LEFT: 50 " MATRIX_BRIGHT "│                 │" RED " RIGHT:150" MATRIX_BRIGHT "│\n");
    printf("              └─────┬─────┘                 └─────┬─────┘\n");
    printf("           ┌───────┴───────┐             ┌───────┴───────┐\n");
    printf("      ┌────┴────┐    ┌────┴────┐   ┌────┴────┐    ┌────┴────┐\n");
    printf("      │" DIM " 25    " MATRIX_BRIGHT "│    │" DIM " 75    " MATRIX_BRIGHT "│   │" DIM " 125   " MATRIX_BRIGHT "│    │" DIM " 175   " MATRIX_BRIGHT "│\n");
    printf("      └─────────┘    └─────────┘   └─────────┘    └─────────┘\n");
    printf(RESET);

    /* 使用顺序二叉树 */
    SeqBinaryTree sbt = SeqBinaryTree_Create(15);
    (void)sbt; /* 用于演示创建，实际使用在后续版本 */

    printf(MATRIX_GREEN "\n  [TREE] Tree structure created with capacity: 15 nodes\n" RESET);
    printf(MATRIX_GREEN "  [TREE] Analyzing traversal patterns...\n\n" RESET);

    /* 遍历顺序展示 */
    printf("  " MATRIX_DIM "┌─────────────────────────────────────────────────────┐\n");
    printf("  │" RESET " " MATRIX_BRIGHT "Pre-order  (VLR):" RESET " ROOT → LEFT → RIGHT           " MATRIX_DIM "│\n");
    printf("  │" RESET " " MATRIX_BRIGHT "In-order   (LVR):" RESET " LEFT → ROOT → RIGHT           " MATRIX_DIM "│\n");
    printf("  │" RESET " " MATRIX_BRIGHT "Post-order (LRV):" RESET " LEFT → RIGHT → ROOT           " MATRIX_DIM "│\n");
    printf("  │" RESET " " MATRIX_BRIGHT "Level-order    :" RESET " Layer by layer (BFS)          " MATRIX_DIM "│\n");
    printf("  └─────────────────────────────────────────────────────┘\n" RESET);

    printf(MATRIX_GREEN "\n  [TREE] Decision pathways mapped successfully.\n" RESET);

    print_mini_separator();
}

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                         DEMO 6: 排序 - 数据净化                               */
/* ═══════════════════════════════════════════════════════════════════════════ */

static void demo_sort_data_purification(void) {
    print_separator("DATA PURIFICATION :: Sorting Algorithms Benchmark");

    #define DATA_SIZE 12
    ElementType original[DATA_SIZE];
    ElementType data[DATA_SIZE];

    /* 生成随机数据 */
    printf(MATRIX_GREEN "\n  [SORT] Generating chaotic data stream...\n\n" RESET);

    srand((unsigned)time(NULL));
    printf("  " MATRIX_DIM "Raw data: " RESET "[");
    for (int i = 0; i < DATA_SIZE; i++) {
        original[i] = (rand() % 900) + 100;
        printf(RED " %3d" RESET, (int)original[i]);
    }
    printf(" ]\n\n");

    /* 测试不同排序算法 */
    typedef struct {
        const char *name;
        void (*sort)(ElementType*, int);
    } SortAlgorithm;

    SortAlgorithm algorithms[] = {
        {"Selection Sort", SelectionSort},
        {"Bubble Sort", BubbleSort}
        /* HeapSort 和 ShellSort 尚未实现 */
    };
    int algo_count = sizeof(algorithms) / sizeof(algorithms[0]);

    for (int a = 0; a < algo_count; a++) {
        /* 复制数据 */
        memcpy(data, original, sizeof(original));

        printf("  " MATRIX_BRIGHT "%-16s" RESET " : ", algorithms[a].name);

        /* 动画效果 */
        printf(MATRIX_DIM "[");
        for (int i = 0; i < 15; i++) {
            printf("░");
        }
        printf("]" RESET);
        fflush(stdout);

        /* 返回并覆盖 */
        printf("\r  " MATRIX_BRIGHT "%-16s" RESET " : ", algorithms[a].name);
        printf(MATRIX_GREEN "[");

        algorithms[a].sort(data, DATA_SIZE);

        for (int i = 0; i < 15; i++) {
            printf("█");
            fflush(stdout);
            delay_ms(20);
        }
        printf("]" RESET);

        /* 显示排序结果 */
        printf(" → [");
        for (int i = 0; i < DATA_SIZE; i++) {
            printf(CYAN " %3d" RESET, (int)data[i]);
        }
        printf(" ]\n");

        delay_ms(100);
    }

    /* 测试 QuickSort 和 MergeSort */
    printf("\n  " MATRIX_DIM "───── Advanced Algorithms ─────\n\n" RESET);

    memcpy(data, original, sizeof(original));
    printf("  " MATRIX_BRIGHT "Quick Sort      " RESET " : ");
    QuickSort(data, DATA_SIZE);
    printf("[");
    for (int i = 0; i < DATA_SIZE; i++) {
        printf(MATRIX_BRIGHT " %3d" RESET, (int)data[i]);
    }
    printf(" ] " MATRIX_GREEN "✓\n" RESET);

    memcpy(data, original, sizeof(original));
    printf("  " MATRIX_BRIGHT "Merge Sort      " RESET " : ");
    MergeSort(data, DATA_SIZE);
    printf("[");
    for (int i = 0; i < DATA_SIZE; i++) {
        printf(MATRIX_BRIGHT " %3d" RESET, (int)data[i]);
    }
    printf(" ] " MATRIX_GREEN "✓\n" RESET);

    memcpy(data, original, sizeof(original));
    printf("  " MATRIX_BRIGHT "Insertion Sort  " RESET " : ");
    InsertionSort(data, DATA_SIZE);
    printf("[");
    for (int i = 0; i < DATA_SIZE; i++) {
        printf(MATRIX_BRIGHT " %3d" RESET, (int)data[i]);
    }
    printf(" ] " MATRIX_GREEN "✓\n" RESET);

    printf(MATRIX_GREEN "\n  [SORT] Data purification complete. Entropy eliminated.\n" RESET);

    print_mini_separator();
}

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                         DEMO 7: 综合演示 - 黑客入侵模拟                        */
/* ═══════════════════════════════════════════════════════════════════════════ */

static void demo_hack_simulation(void) {
    print_separator("SYSTEM BREACH SIMULATION :: All Structures Active");

    printf(MATRIX_GREEN "\n  [BREACH] Initiating multi-vector attack simulation...\n\n" RESET);

    /* 创建所有数据结构 */
    SeqList payloads = SeqList_Create();
    LinkedListHead targets = LinkedList_Create();
    SeqStack exploits = SeqStack_Create(10);
    LinkedStackHead backdoors = LinkedStack_Create();
    SeqQueue commands = SeqQueue_Create(10);
    LinkedQueue responses = LinkedQueue_Create();
    (void)responses; /* 用于演示创建，后续扩展使用 */

    /* 阶段 1: 侦察 */
    printf("  " MATRIX_BRIGHT "PHASE 1: RECONNAISSANCE\n" RESET);
    printf("  " MATRIX_DIM "├──" RESET " Scanning targets with LinkedList...\n");
    for (int i = 0; i < 5; i++) {
        LinkedList_InsertAtNodePosition(targets, 192168000001 + i, i + 1);
        printf("  " MATRIX_DIM "│   └──" GREEN " Target %d identified\n" RESET, i + 1);
        delay_ms(100);
    }

    /* 阶段 2: 武器化 */
    printf("\n  " MATRIX_BRIGHT "PHASE 2: WEAPONIZATION\n" RESET);
    printf("  " MATRIX_DIM "├──" RESET " Loading payloads into SeqList...\n");
    for (int i = 0; i < 4; i++) {
        SeqList_InsertAt(payloads, (ElementType)(0xDEAD0000 + i), i);
        printf("  " MATRIX_DIM "│   └──" RED " Payload 0x%08X loaded\n" RESET, 0xDEAD0000 + i);
        delay_ms(100);
    }

    /* 阶段 3: 交付 */
    printf("\n  " MATRIX_BRIGHT "PHASE 3: DELIVERY\n" RESET);
    printf("  " MATRIX_DIM "├──" RESET " Queueing attack commands...\n");
    for (int i = 0; i < 3; i++) {
        SeqQueue_Enqueue(commands, (ElementType)(i + 1));
        printf("  " MATRIX_DIM "│   └──" YELLOW " Command %d queued\n" RESET, i + 1);
        delay_ms(100);
    }

    /* 阶段 4: 利用 */
    printf("\n  " MATRIX_BRIGHT "PHASE 4: EXPLOITATION\n" RESET);
    printf("  " MATRIX_DIM "├──" RESET " Pushing exploits to stack...\n");
    for (int i = 0; i < 3; i++) {
        SeqStack_Push(exploits, (ElementType)(0xBEEF0000 + i));
        printf("  " MATRIX_DIM "│   └──" MAGENTA " Exploit 0x%08X pushed\n" RESET, 0xBEEF0000 + i);
        delay_ms(100);
    }

    /* 阶段 5: 安装 */
    printf("\n  " MATRIX_BRIGHT "PHASE 5: INSTALLATION\n" RESET);
    printf("  " MATRIX_DIM "├──" RESET " Deploying backdoors via LinkedStack...\n");
    for (int i = 0; i < 2; i++) {
        LinkedStack_Push(backdoors, (ElementType)(0xC0DE0000 + i));
        printf("  " MATRIX_DIM "│   └──" CYAN " Backdoor 0x%08X installed\n" RESET, 0xC0DE0000 + i);
        delay_ms(100);
    }

    /* 最终状态 */
    printf("\n  " MATRIX_BRIGHT "═══════════════════════════════════════════════════\n" RESET);
    printf("  " MATRIX_GREEN "  BREACH SIMULATION COMPLETE\n" RESET);
    printf("  " MATRIX_DIM "  ─────────────────────────────────────────────────\n" RESET);
    printf("    Targets scanned    : " CYAN "%lld\n" RESET, (long long)LinkedList_GetLength(targets));
    printf("    Payloads loaded    : " RED "%d\n" RESET, SeqList_GetLength(payloads));
    printf("    Commands executed  : " YELLOW "3\n" RESET);
    printf("    Exploits deployed  : " MAGENTA "3\n" RESET);
    printf("    Backdoors active   : " CYAN "2\n" RESET);
    printf("  " MATRIX_BRIGHT "═══════════════════════════════════════════════════\n" RESET);

    /* 清理 */
    LinkedList_Destroy(targets);
    LinkedStack_Delete(backdoors);
    SeqQueue_Destroy(commands);

    print_mini_separator();
}

/* ═══════════════════════════════════════════════════════════════════════════ */
/*                               主函数                                         */
/* ═══════════════════════════════════════════════════════════════════════════ */

int main(void) {
    srand((unsigned)time(NULL));

    clear_screen();

    /* Matrix 数字雨开场动画 */
    matrix_rain_animation(ANIMATION_FRAMES);

    /* 显示 Logo */
    print_matrix_logo();

    printf(MATRIX_GREEN "  Press ENTER to jack into the Matrix..." RESET);
    getchar();
    clear_screen();
    print_matrix_logo();

    /* 运行所有演示 */
    demo_seqlist_system_init();
    delay_ms(500);

    demo_linkedlist_network_trace();
    delay_ms(500);

    demo_stack_call_trace();
    delay_ms(500);

    demo_queue_message_processing();
    delay_ms(500);

    demo_binary_tree_decision();
    delay_ms(500);

    demo_sort_data_purification();
    delay_ms(500);

    demo_hack_simulation();

    /* 结束语 */
    printf(MATRIX_GREEN "\n");
    printf("  ╔═══════════════════════════════════════════════════════════════════════════╗\n");
    printf("  ║                                                                           ║\n");
    printf("  ║  " MATRIX_BRIGHT "\"The Matrix is everywhere. It is all around us.\"" MATRIX_GREEN "                     ║\n");
    printf("  ║  " MATRIX_DIM "                                        - Morpheus" MATRIX_GREEN "                    ║\n");
    printf("  ║                                                                           ║\n");
    printf("  ║  " RESET "All data structures demonstrated successfully." MATRIX_GREEN "                        ║\n");
    printf("  ║  " RESET "SeqList | LinkedList | SeqStack | LinkedStack | SeqQueue | LinkedQueue" MATRIX_GREEN "  ║\n");
    printf("  ║  " RESET "SeqBinaryTree | Sort Algorithms" MATRIX_GREEN "                                        ║\n");
    printf("  ║                                                                           ║\n");
    printf("  ╚═══════════════════════════════════════════════════════════════════════════╝\n\n");
    printf(RESET);

    printf(MATRIX_BRIGHT "  Session terminated. Welcome back to reality.\n\n" RESET);

    return 0;
}

