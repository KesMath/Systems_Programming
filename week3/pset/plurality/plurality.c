#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    print_winner();


//     //TESTING!!!
//     int array[] = {2, 1, 3, 7, 1};
//     string arr[] = {"pat", "mat", "cat", "dat", "frat"};

//     for (int i = 0; i < 5; i++)
//     {
//         candidates[i].name = arr[i];
//         candidates[i].votes = array[i];
//     }

//     print_winner();
//     for (int i = 0; i < 5; i++)
//     {
//         printf("%i\n", candidates[i].votes);
//     }
//     //DONE TESTING!!!
}

// Update vote totals given a new vote
// A Better approach would be to use dictionary which would reduce O(n*m) runtime in main() to O(n)
// but for the sake of this pset, the instructors want students to get used to structs
bool vote(string name)
{
    for(int i = 0; i < candidate_count; i++){
        if(strcmp(name, candidates[i].name) == 0){
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

void swap(candidate arr[], int index1, int index2){
    candidate temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

void selection_sort(void){
    // selection sort candidate array from least to greatest votes
    //TODO: for Testing Purposes ONLY!
    //int candidate_count = 5;
    for(int i = 0; i < candidate_count; i++){
        for(int j = i + 1; j < candidate_count; j++){
            if(candidates[i].votes > candidates[j].votes){
                swap(candidates, i, j);
            }
        }
    }
}

// Print the winner (or winners) of the election
// We can sort array based on vote count and print accordingly 
void print_winner(void)
{
    // selection sort candidate array from least to greatest votes
    selection_sort();

    // scenario when we have a single winner
    if(candidates[candidate_count - 1].votes > candidates[candidate_count - 2].votes){
        printf("%s\n", candidates[candidate_count - 1].name);
    }
    else{
        // scenario when we have multiple winners
        // we essentially iterate backwards (since candidates with largest votes are on the right-hand-side)
        // and break out when all candidates with tied scores are printed
        for(; candidate_count > 0; candidate_count--){
            if(candidates[candidate_count - 1].votes == candidates[candidate_count - 2].votes){
                printf("%s\n", candidates[candidate_count - 1].name);
            }
            else{
                break;
            }
        }
        // print trailing candidate who tied since comparison above only prints one at a time
        printf("%s\n",candidates[candidate_count - 1].name);
    }
    return;
}