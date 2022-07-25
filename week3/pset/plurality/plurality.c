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

    // Display winner of election
    print_winner();
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

// Print the winner (or winners) of the election
// implementation would be better with some dynamically allocated array
void print_winner(void)
{ 
    int highest_scoring_candidate_index[candidate_count];
    int winner_cout = 0;
    for(int i = 0; i < candidate_count - 1; i++){
        if(candidates[i].votes > candidates[i+1].votes){
            highest_scoring_candidate_index[i] = i;
        }
        else if(candidates[i].votes < candidates[i+1].votes){
            highest_scoring_candidate_index[i] = i+1; 
        }
        else{
            // add both winners to list
            highest_scoring_candidate_index[i] = i;
            highest_scoring_candidate_index[i+1] = i+1;  
            winner_cout+=2;
        }
    }
    
    if (winner_cout < 1){
        printf("%s\n", candidates[highest_scoring_candidate_index[0]].name);
    }
    else{
        for(int i = 0; i < winner_cout; i++){
            printf("%s\n", candidates[highest_scoring_candidate_index[i]].name);
        }
    }
    return;
}