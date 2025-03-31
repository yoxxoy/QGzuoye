#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 1000

// 生成测试数据文件
void generate_test_data(const char* filename, int size) {
    FILE* file = fopen(filename, "w"); // 以写模式打开文件
    if (file == NULL) {
        perror("打印错误信息"); // 打印错误信息
        return;
    }

    srand(time(NULL)); // 使用当前时间初始化随机数生成器

    int i;
    for (i = 0; i < size; i++) {
        int num = rand() % 1000; // 生成0到999之间的随机数
        fprintf(file, "%d\n", num); // 将随机数写入文件
    }

    fclose(file); // 关闭文件
}

// 插入排序算法
void insertion_sort(int arr[], int size) {
    int i, j, key;

    for (i = 1; i < size; i++) {
        key = arr[i]; // 当前要插入的元素
        j = i - 1;

        // 将大于key的元素向后移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // 将key插入到正确的位置
    }
}

// 归并排序的合并函数
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1; // 左半部分的大小
    int n2 = right - mid;    // 右半部分的大小

    // 创建临时数组存储左右半部分
    int L[n1], R[n2];

    // 复制数据到临时数组
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // 合并临时数组到原数组
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // 复制剩余元素
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 归并排序算法
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // 计算中间位置

        // 递归排序左右两部分
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // 合并排序后的两部分
        merge(arr, left, mid, right);
    }
}

// 快速排序的分区函数
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为基准
    int i = (low - 1);     // 小于基准的元素的索引
	int j;
    for ( j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++; // 增加小于基准的元素的索引
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp; // 交换元素
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp; // 将基准元素放到正确的位置
    return i + 1; // 返回基准元素的位置
}

// 快速排序算法
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // 获取分区点

        // 递归排序左右两部分
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// 计数排序算法
void count_sort(int arr[], int size) {
    int output[MAX_SIZE]; // 存储排序后的结果
    int count[MAX_SIZE];  // 计数数组
    int max = arr[0];     // 找到数组中的最大值
	int i;
    // 寻找最大值
    for ( i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    memset(count, 0, sizeof(count)); // 初始化计数数组为0

    // 统计每个元素的出现次数
    for ( i = 0; i < size; i++)
        count[arr[i]]++;

    // 计算累计计数
    for ( i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // 根据计数数组重建排序后的数组
    for ( i = size - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // 将排序后的数组复制回原数组
    for ( i = 0; i < size; i++)
        arr[i] = output[i];
}

// 基数计数排序算法
void radix_count_sort(int arr[], int size) {
    int output[MAX_SIZE]; // 存储排序后的结果
    int count[10];        // 计数数组（0-9）
    int max = arr[0];     // 找到数组中的最大值
	int i,exp;
    // 寻找最大值
    for ( i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    // 对每一位进行计数排序
    for ( exp = 1; max / exp > 0; exp *= 10) {
        memset(count, 0, sizeof(count)); // 初始化计数数组为0

        // 统计每一位数字的出现次数
        for ( i = 0; i < size; i++)
            count[(arr[i] / exp) % 10]++;

        // 计算累计计数
        for ( i = 1; i < 10; i++)
            count[i] += count[i - 1];

        // 根据计数数组重建排序后的数组
        for ( i = size - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        // 将排序后的数组复制回原数组
        for ( i = 0; i < size; i++)
            arr[i] = output[i];
    }
}

// 读取文件数据并排序
void read_and_sort_data(const char* filename, void (*sort_func)(int[], int)) {
    FILE* file = fopen(filename, "r"); // 以读模式打开文件
    if (file == NULL) {
        perror("打印错误信息"); // 打印错误信息
        return;
    }
	int i;
    int arr[MAX_SIZE]; // 存储读取的数据
    int size = 0;      // 数据的大小

    // 读取文件中的数据
    while (fscanf(file, "%d", &arr[size]) == 1)
        size++;

    fclose(file); // 关闭文件

    // 记录排序开始时间
    clock_t start = clock();
    sort_func(arr, size); // 调用排序函数
    clock_t end = clock(); // 记录排序结束时间

    // 打印排序后的数据
    printf("Sorted data:\n");
    for ( i = 0; i < size; i++)
        printf("%d ", arr[i]);

    // 计算并打印排序所需的时间
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sorting took %f seconds\n", time_taken);
}

int main() {
    const char* filename = "test_data.txt"; // 测试数据文件名
    int size = 1000;                         // 生成的数据数量

    // 生成测试数据并保存到文件
    generate_test_data(filename, size);

    // 使用不同的排序算法对数据进行排序并测量时间
    read_and_sort_data(filename, (void (*)(int[], int))insertion_sort);
    read_and_sort_data(filename, (void (*)(int[], int))merge_sort);
    read_and_sort_data(filename, (void (*)(int[], int))quick_sort);
    read_and_sort_data(filename, (void (*)(int[], int))count_sort);
    read_and_sort_data(filename, (void (*)(int[], int))radix_count_sort);

    return 0;
}
