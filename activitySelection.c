// Write a C program to solve Activity Selection Problem using Greedy approach.


#include <stdio.h>

struct Activity {
    int start;
    int finish;
};

void swap(struct Activity *a, struct Activity *b) {
    struct Activity temp = *a;
    *a = *b;
    *b = temp;
}

void sortActivities(struct Activity arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].finish > arr[j + 1].finish) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void activitySelection(struct Activity arr[], int n) {
    sortActivities(arr, n);

    printf("Selected activities are:\n");

    int lastSelected = 0;
    printf("(%d, %d)\n", arr[lastSelected].start, arr[lastSelected].finish);

    for (int i = 1; i < n; i++) {
        if (arr[i].start >= arr[lastSelected].finish) {
            printf("(%d, %d)\n", arr[i].start, arr[i].finish);
            lastSelected = i;
        }
    }
}

int main() {
    int n;
    printf("Enter number of activities: ");
    scanf("%d", &n);

    struct Activity arr[n];

    printf("Enter start and finish times of activities:\n");
    for (int i = 0; i < n; i++) {
        printf("Activity %d: ", i + 1);
        scanf("%d %d", &arr[i].start, &arr[i].finish);
    }

    activitySelection(arr, n);

    return 0;
}
