#include "sort.h"

//insertion sort function, where insertionSequence is the vector of size sizeN
void Sorts::insertionSort(std::vector <int> &insertionSequence, int sizeN){

    int i, j, k = 0;
    for (i = 1; i < sizeN; i++){
        j = i;
        k = insertionSequence[i];
        while (j > 0 and k < insertionSequence[j - 1]){
            insertionSequence[j] = insertionSequence[j - 1];
            j--;
        }
        insertionSequence[j] = k;
    }
}

void Sorts::merge(std::vector<int>& arr, int left, int mid, int right) {
    int i = left;       // Index for left subarray
    int j = mid + 1;    // Index for right subarray
    int k = 0;          // Index for temporary array

    std::vector<int> temp(right - left + 1); // Temporary array

    // Merge the two subarrays into the temporary array
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    // Copy the remaining elements of the left subarray, if any
    while (i <= mid)
        temp[k++] = arr[i++];

    // Copy the remaining elements of the right subarray, if any
    while (j <= right)
        temp[k++] = arr[j++];

    // Copy the merged elements back to the original array
    for (i = left, k = 0; i <= right; i++, k++)
        arr[i] = temp[k];
}

 void Sorts::mergeSort(std::vector<int>& arr, int left, int right, SDL_Renderer *renderer) {
        if (left < right) {
            int mid = left + (right - left) / 2; // Calculate the mid-point

            // Recursively divide the array into two halves
            mergeSort(arr, left, mid, renderer);
            mergeSort(arr, mid + 1, right, renderer);

            // Merge the sorted halves
            merge(arr, left, mid, right);

            renderArray(renderer, arr);
            SDL_Delay(FRAME_DELAY);
        }
    }

int Sorts::quickSort(std::vector <int> *quick, int left, int right){
    {
        int i = left;
        int j = right + 1;
        while (true) {

            // while quick[i] < pivot, increase i
            while (quick[++i] < quick[left])
                if (i == right) break;

            // while quick[i] > pivot, decrease j
            while (quick[left] < quick[--j])

                if (j == left) break;

            // if i and j cross exit theloop
            if(i >= j) break;

            // swap quick[i], quick[j]
            std::swap(quick[i], quick[j]);
        }
        // swap the pivot with quick[j]
        std::swap(quick[left], quick[j]);

        //return pivot's position
        return j;
    }
}
// recursively calls quicksort
void Sorts::r_quicksort(std::vector<int> *quick, int left, int right){
    if (right <= left){
        return;

    }
    int pivot = quickSort(quick, left, right);

    r_quicksort(quick, left, pivot - 1);

    r_quicksort(quick, pivot + 1, right);
}
/**
* This is radix sort. Radix sort is used to sort arrays of numbers that all have
* the same number of digits. This sort is NOT recommended on numbers of varying
* lengths.
* @param unsorted
* @param numDigits
* @return void
*/
void Sorts::radixSort(std::vector<int> &arr, int numDigits) {

    for (int i = 0 ; i < numDigits ; i++) {

        // create empty containers that we will organize into
        std::vector< std::vector<int> > containers(10);

        // for num in arr
        for (int v : arr)
            containers[(v / (int)std::pow(10, i)) % 10].push_back(v);

        // clear out arr
        arr.clear();

        // Rinse & Repeat
        for (const std::vector<int> &c : containers)
            arr.insert(arr.end(), c.begin(), c.end());

    }

}

void Sorts::insert(int num) {
    sequence.push_back(num);
}

void Sorts::intializeVectors(std::vector<int> sequence) {
    insertionSequence = sequence;
    mergeSequence = sequence;
    quickSequence = sequence;
    radixSequence = sequence;
}

bool Sorts::initializeSDL(SDL_Window *&window, SDL_Renderer *&renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Merge Sort Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return true;
}

void Sorts::handleEvents(bool &quit) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
    }
}

void Sorts::renderArray(SDL_Renderer *renderer, const std::vector<int> &arr) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int barWidth = SCREEN_WIDTH / arr.size();
    int maxHeight = SCREEN_HEIGHT - 20;

    for (size_t i = 0; i < arr.size(); ++i) {
        int barHeight = (arr[i] * maxHeight) / *std::max_element(arr.begin(), arr.end() + arr.size());
        int x = i * (barWidth + GAP);
        int y = SCREEN_HEIGHT - barHeight;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = {x, y, barWidth, barHeight};
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

void Sorts::initializeVisual() {
    intializeVectors(sequence);

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    initializeSDL(window, renderer);
    bool quit = false;

    if (mode == 0) {
        while (!quit) {
            handleEvents(quit);
            mergeSort(mergeSequence, 0, mergeSequence.size() - 1, renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Sorts::setMode(int givenMode){
    mode = givenMode;
}
