#include <stdio.h>

#define MAX 100

struct Package {
    int id;
    float value;
    float weight;
    float ratio;
    float selected;
};

struct Package p[MAX];
int n = 0;
float capacity = 0;
int detailsEntered = 0;
int ratioCalculated = 0;
int sorted = 0;

void enterDetails() {
    int i;

    printf("\nEnter number of packages: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nEnter value of Package %d: ", i + 1);
        scanf("%f", &p[i].value);

        printf("Enter weight of Package %d: ", i + 1);
        scanf("%f", &p[i].weight);

        p[i].ratio = 0;
        p[i].selected = 0;
    }

    printf("\nEnter maximum carrying capacity: ");
    scanf("%f", &capacity);

    detailsEntered = 1;
    ratioCalculated = 0;
    sorted = 0;

    printf("\nPackage details entered successfully!\n");
}

void calculateRatio() {
    int i;

    if (!detailsEntered) {
        printf("\nPlease enter package details first.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        p[i].ratio = p[i].value / p[i].weight;
    }

    ratioCalculated = 1;

    printf("\nValue/Weight ratios calculated successfully!\n");

    printf("\nPackage\tValue\tWeight\tRatio\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               p[i].id, p[i].value, p[i].weight, p[i].ratio);
    }
}

void sortPackages() {
    int i, j;
    struct Package temp;

    if (!ratioCalculated) {
        printf("\nPlease calculate the ratio first.\n");
        return;
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {

            if (p[j].ratio < p[j + 1].ratio) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    sorted = 1;

    printf("\nPackages sorted in decreasing order of Value/Weight ratio.\n");

    printf("\nPackage\tValue\tWeight\tRatio\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               p[i].id, p[i].value, p[i].weight, p[i].ratio);
    }
}

void findMaximumValue() {
    int i;
    float remainingCapacity;
    float totalValue = 0;
    float totalWeight = 0;

    if (!sorted) {
        printf("\nPlease calculate ratio and sort packages first.\n");
        return;
    }

    remainingCapacity = capacity;

    for (i = 0; i < n; i++) {
        p[i].selected = 0;
    }

    for (i = 0; i < n; i++) {

        if (remainingCapacity <= 0)
            break;

        if (p[i].weight <= remainingCapacity) {

            p[i].selected = 1;
            remainingCapacity -= p[i].weight;

            totalWeight += p[i].weight;
            totalValue += p[i].value;
        }

        else {

            p[i].selected = remainingCapacity / p[i].weight;

            totalWeight += remainingCapacity;
            totalValue += p[i].value * p[i].selected;

            remainingCapacity = 0;
        }
    }

    printf("\nTotal weight used = %.2f", totalWeight);
    printf("\nMaximum value obtained = %.2f\n", totalValue);
}

void displaySelectedPackages() {
    int i;
    float remainingCapacity;
    float totalValue = 0;
    float totalWeight = 0;

    if (!sorted) {
        printf("\nPlease calculate ratio and sort packages first.\n");
        return;
    }

    remainingCapacity = capacity;

    for (i = 0; i < n; i++) {
        p[i].selected = 0;
    }

    for (i = 0; i < n; i++) {

        if (remainingCapacity <= 0)
            break;

        if (p[i].weight <= remainingCapacity) {

            p[i].selected = 1;

            remainingCapacity -= p[i].weight;
            totalWeight += p[i].weight;
            totalValue += p[i].value;
        }
        else {

            p[i].selected = remainingCapacity / p[i].weight;

            totalWeight += remainingCapacity;
            totalValue += p[i].value * p[i].selected;

            remainingCapacity = 0;
        }
    }

    printf("\nSelected Packages:\n");
    printf("Package\tFraction\tWeight Used\tValue Obtained\n");

    for (i = 0; i < n; i++) {
        if (p[i].selected > 0) {

            printf("%d\t%.2f\t\t%.2f\t\t%.2f\n",
                   p[i].id,
                   p[i].selected,
                   p[i].weight * p[i].selected,
                   p[i].value * p[i].selected);
        }
    }

    printf("\nTotal Weight Used = %.2f", totalWeight);
    printf("\nMaximum Value = %.2f\n", totalValue);
}

void displayDetails() {
    int i;

    if (!detailsEntered) {
        printf("\nPlease enter package details first.\n");
        return;
    }

    printf("\nPackage Details:\n");
    printf("Package\tValue\tWeight\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%.2f\t%.2f\n",
               p[i].id, p[i].value, p[i].weight);
    }

    printf("Vehicle Capacity = %.2f\n", capacity);
}

int main() {
    int choice;

    do {
        printf("\n========== FRACTIONAL KNAPSACK ==========\n");
        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");
        printf("=========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                enterDetails();
                break;

            case 2:
                displayDetails();
                break;

            case 3:
                calculateRatio();
                break;

            case 4:
                sortPackages();
                break;

            case 5:
                findMaximumValue();
                break;

            case 6:
                displaySelectedPackages();
                break;

            case 7:
                printf("\nProgram exited successfully.\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}
