#include <stdio.h>
#include <stdlib.h>

int removeDuplicates(int *nums, int numsSize) {
    int i = 0, j = 1;
    int count = 0; // Counter for unique elements
    
    while (j < numsSize) {
        if (nums[j] == nums[i])
            nums[i] = '_';
        i++;
        j++;
    }
    j = 0; i = -1;
    while (++i < numsSize){
        if (nums[i] == '_')
            i++;
        else if (nums[i] >= '0' && nums[i] <= '9'){
            nums[j] = nums[i]; 
        }
    }
    return count;
}

int main() {
    int nums[] = {1, 1, 2, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    
    printf("Original array: ");
    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    
    int k = removeDuplicates(nums, numsSize);
    
    printf("Modified array: ");
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == '_')
            printf("_ ");
        else
            printf("%d ", nums[i]);
    }
    printf("\n");
    
    printf("Number of unique elements: %d\n", k);
    
    return 0;
}