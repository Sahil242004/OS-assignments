#include <stdio.h>

int search(int frames[], int size, int page) {
    for(int i = 0; i < size; i++) {
        if(frames[i] == page)
            return 1;  // found (hit)
    }
    return 0;  // not found (page fault)
}

int predict(int pages[], int frames[], int n, int capacity, int index) {
    int res = -1, farthest = index;

    for(int i = 0; i < capacity; i++) {
        int j;
        for(j = index; j < n; j++) {
            if(frames[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if(j == n)  // frame page not found in future, best to replace this
            return i;
    }
    if(res == -1)
        return 0;
    else
        return res;
}

int main() {
    int n, capacity, fault = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter page reference sequence:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    int frames[capacity];
    for(int i = 0; i < capacity; i++) {
        frames[i] = -1;  // initialize frames as empty
    }

    printf("\nPage\tFrames\n");

    for(int i = 0; i < n; i++) {
        int page = pages[i];

        if(search(frames, capacity, page)) {
            // Page hit, no fault
        } else {
            fault++;

            // Find frame to replace using optimal strategy
            int replace_index = predict(pages, frames, n, capacity, i + 1);

            frames[replace_index] = page;
        }

        // Print current frames
        printf("%d\t", page);
        for(int j = 0; j < capacity; j++) {
            if(frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", fault);

    return 0;
}

/*
PSEUDOCODE (Simple Language):

1. Initialize empty frames.
2. For each page in the reference sequence:
   a. If page is already in frames (hit), do nothing.
   b. Else (page fault):
      - Find the frame whose page will not be used for the longest time in the future.
      - If a page is never used again, replace that immediately.
      - Replace that frame with current page.
3. Print frames after each page reference.
4. At the end, print total page faults.
*/
