#include <stdio.h>

int main() {
    int n, capacity, i, j, k, page, fault = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter page reference sequence:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    int frames[capacity];
    int time[capacity];  // stores last used time for each frame
    for(i = 0; i < capacity; i++) {
        frames[i] = -1;    // initialize frames as empty
        time[i] = 0;
    }

    int current_time = 0;

    printf("\nPage\tFrames\n");

    for(i = 0; i < n; i++) {
        page = pages[i];
        int found = 0;
        current_time++;

        // Check if page is already in frames (hit)
        for(j = 0; j < capacity; j++) {
            if(frames[j] == page) {
                found = 1;
                time[j] = current_time;  // update last used time
                break;
            }
        }

        if(!found) {
            fault++;

            // Find least recently used frame
            int lru_index = 0;
            int min_time = time[0];
            for(j = 1; j < capacity; j++) {
                if(time[j] < min_time) {
                    min_time = time[j];
                    lru_index = j;
                }
            }

            // Replace LRU frame with current page
            frames[lru_index] = page;
            time[lru_index] = current_time;
        }

        // Print current frame status
        printf("%d\t", page);
        for(k = 0; k < capacity; k++) {
            if(frames[k] != -1)
                printf("%d ", frames[k]);
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

1. Initialize empty frames and an array to store last used time for each frame.
2. For each page in the reference sequence:
   a. Check if page is already in any frame (hit).
      - If yes, update the last used time of that frame.
   b. If not found (page fault):
      - Find the frame which was least recently used (smallest last used time).
      - Replace that frame with the current page.
      - Update last used time for that frame.
3. Print frames after each page reference.
4. At the end, print total page faults.
*/
