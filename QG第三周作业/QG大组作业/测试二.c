#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 1000

// ���ɲ��������ļ�
void generate_test_data(const char* filename, int size) {
    FILE* file = fopen(filename, "w"); // ��дģʽ���ļ�
    if (file == NULL) {
        perror("��ӡ������Ϣ"); // ��ӡ������Ϣ
        return;
    }

    srand(time(NULL)); // ʹ�õ�ǰʱ���ʼ�������������

    int i;
    for (i = 0; i < size; i++) {
        int num = rand() % 1000; // ����0��999֮��������
        fprintf(file, "%d\n", num); // �������д���ļ�
    }

    fclose(file); // �ر��ļ�
}

// ���������㷨
void insertion_sort(int arr[], int size) {
    int i, j, key;

    for (i = 1; i < size; i++) {
        key = arr[i]; // ��ǰҪ�����Ԫ��
        j = i - 1;

        // ������key��Ԫ������ƶ�
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // ��key���뵽��ȷ��λ��
    }
}

// �鲢����ĺϲ�����
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1; // ��벿�ֵĴ�С
    int n2 = right - mid;    // �Ұ벿�ֵĴ�С

    // ������ʱ����洢���Ұ벿��
    int L[n1], R[n2];

    // �������ݵ���ʱ����
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // �ϲ���ʱ���鵽ԭ����
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

    // ����ʣ��Ԫ��
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

// �鲢�����㷨
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // �����м�λ��

        // �ݹ���������������
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // �ϲ�������������
        merge(arr, left, mid, right);
    }
}

// ��������ķ�������
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // ѡ�����һ��Ԫ����Ϊ��׼
    int i = (low - 1);     // С�ڻ�׼��Ԫ�ص�����
	int j;
    for ( j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++; // ����С�ڻ�׼��Ԫ�ص�����
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp; // ����Ԫ��
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp; // ����׼Ԫ�طŵ���ȷ��λ��
    return i + 1; // ���ػ�׼Ԫ�ص�λ��
}

// ���������㷨
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // ��ȡ������

        // �ݹ���������������
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// ���������㷨
void count_sort(int arr[], int size) {
    int output[MAX_SIZE]; // �洢�����Ľ��
    int count[MAX_SIZE];  // ��������
    int max = arr[0];     // �ҵ������е����ֵ
	int i;
    // Ѱ�����ֵ
    for ( i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    memset(count, 0, sizeof(count)); // ��ʼ����������Ϊ0

    // ͳ��ÿ��Ԫ�صĳ��ִ���
    for ( i = 0; i < size; i++)
        count[arr[i]]++;

    // �����ۼƼ���
    for ( i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // ���ݼ��������ؽ�����������
    for ( i = size - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // �����������鸴�ƻ�ԭ����
    for ( i = 0; i < size; i++)
        arr[i] = output[i];
}

// �������������㷨
void radix_count_sort(int arr[], int size) {
    int output[MAX_SIZE]; // �洢�����Ľ��
    int count[10];        // �������飨0-9��
    int max = arr[0];     // �ҵ������е����ֵ
	int i,exp;
    // Ѱ�����ֵ
    for ( i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    // ��ÿһλ���м�������
    for ( exp = 1; max / exp > 0; exp *= 10) {
        memset(count, 0, sizeof(count)); // ��ʼ����������Ϊ0

        // ͳ��ÿһλ���ֵĳ��ִ���
        for ( i = 0; i < size; i++)
            count[(arr[i] / exp) % 10]++;

        // �����ۼƼ���
        for ( i = 1; i < 10; i++)
            count[i] += count[i - 1];

        // ���ݼ��������ؽ�����������
        for ( i = size - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        // �����������鸴�ƻ�ԭ����
        for ( i = 0; i < size; i++)
            arr[i] = output[i];
    }
}

// ��ȡ�ļ����ݲ�����
void read_and_sort_data(const char* filename, void (*sort_func)(int[], int)) {
    FILE* file = fopen(filename, "r"); // �Զ�ģʽ���ļ�
    if (file == NULL) {
        perror("��ӡ������Ϣ"); // ��ӡ������Ϣ
        return;
    }
	int i;
    int arr[MAX_SIZE]; // �洢��ȡ������
    int size = 0;      // ���ݵĴ�С

    // ��ȡ�ļ��е�����
    while (fscanf(file, "%d", &arr[size]) == 1)
        size++;

    fclose(file); // �ر��ļ�

    // ��¼����ʼʱ��
    clock_t start = clock();
    sort_func(arr, size); // ����������
    clock_t end = clock(); // ��¼�������ʱ��

    // ��ӡ����������
    printf("Sorted data:\n");
    for ( i = 0; i < size; i++)
        printf("%d ", arr[i]);

    // ���㲢��ӡ���������ʱ��
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sorting took %f seconds\n", time_taken);
}

int main() {
    const char* filename = "test_data.txt"; // ���������ļ���
    int size = 1000;                         // ���ɵ���������

    // ���ɲ������ݲ����浽�ļ�
    generate_test_data(filename, size);

    // ʹ�ò�ͬ�������㷨�����ݽ������򲢲���ʱ��
    read_and_sort_data(filename, (void (*)(int[], int))insertion_sort);
    read_and_sort_data(filename, (void (*)(int[], int))merge_sort);
    read_and_sort_data(filename, (void (*)(int[], int))quick_sort);
    read_and_sort_data(filename, (void (*)(int[], int))count_sort);
    read_and_sort_data(filename, (void (*)(int[], int))radix_count_sort);

    return 0;
}
