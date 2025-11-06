int func(int arr[], int size) {
    return arr[size - 1];
}
int main() {
    int nums[] = {5, 10, 15, 20};
    printf("%d", func(nums, 4));
    return 0;
}