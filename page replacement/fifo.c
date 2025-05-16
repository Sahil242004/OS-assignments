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
    for(i = 0; i < capacity; i++) {
        frames[i] = -1;  // initialize frames as empty
    }
    
    int pointer = 0;  // points to the next frame to replace (FIFO order)
    
    printf("\nPage\tFrames\n");
    for(i = 0; i < n; i++) {
        page = pages[i];
        int found = 0;
        
        // Check if page already in frames
        for(j = 0; j < capacity; j++) {
            if(frames[j] == page) {
                found = 1;
                break;
            }
        }
        
        if(!found) {
            // Page fault occurs, replace using FIFO
            frames[pointer] = page;
            pointer = (pointer + 1) % capacity;
            fault++;
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

1. Initialize empty frames and set pointer = 0
2. For each page in the reference sequence:
   a. Check if page is already in any frame (hit)
   b. If yes, no page fault, just continue
   c. If not, page fault occurs:
      - Replace the page at frame indicated by pointer with current page
      - Increment pointer (circularly) to point to next frame for replacement
3. Print frames after each page reference
4. At the end, print total page faults
*/
