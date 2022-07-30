#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid

// The function takes arguments voter, rank, and name.
// If name is a match for the name of a valid candidate,
// then you should update the global preferences array
// to indicate that the voter has that candidate as their rank preference
// (where 0 is the first preference, 1 is the second preference, etc.).

// If the preference is successfully recorded, the function should return true;
// the function should return false otherwise
// (if, for instance, name is not the name of one of the candidates).
bool vote(int voter, int rank, string name)
{
    for(int i = 0; i < candidate_count; i++){
        if(strcmp(name, candidates[i].name) == 0){
            preferences[voter][i] = rank;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
// iterate through preferences[i][0] (which is their top preferred candidate) and persist vote count in candidates arr!
// if person is indeed eliminated, fetch their preferences[i][1] and persist vote in candidates arr!
void tabulate(void)
{
    for(int i = 0; i < voter_count; i++){
        if(!candidates[i].eliminated){
            candidates[preferences[i][0] - 1].votes++;   
        }
        else{
            candidates[preferences[i][1] - 1].votes++;
        }
    }
}


// If any candidate has more than half of the vote, their name should be printed and the function should return true.
// If nobody has won the election yet, the function should return false.
bool print_winner(void)
{
    int half_voter_cout = voter_count / 2;
    for(int i = 0; i < candidate_count; i++){
        if(candidates[i].votes > half_voter_cout){
            printf("%s\n", candidates[i].name);
            return true;
        }
    } 
    return false;
}

// Return the minimum number of votes any remaining candidate has
// min = canndidates[0].votes ... iterate through all (n-1) candidates
// then if candidates[i].vote < min assign that to min, then return min after complete walkthrough!
int find_min(void)
{
    int absolute_min;
    int local_min;
    int local_min_index = 0;

    // getting first vote for non-eliminated candidate 
    for(int i = 0; i < candidate_count; i++){
        if(!candidates[i].eliminated){
            local_min = candidates[i].votes;
            local_min_index = i;
            break;
        }
    }
    //starting comparisons from the next candidate down the line!
    local_min_index++;
    for(; local_min_index < candidate_count; local_min_index++){
        if((!candidates[local_min_index].eliminated) && (candidates[local_min_index].votes < local_min)){
            local_min = candidates[local_min_index].votes;
        }
    }
    absolute_min = local_min;
    return absolute_min;
}

// Return true if the election is tied between all candidates, false otherwise
// "If every remaining candidate has the exact same number of votes, though, eliminating the tied last place candidates means eliminating everyone!
// So in that case, we’ll have to be careful not to eliminate everyone, and just declare the election a tie between all remaining candidates."

bool is_tie(int min)
{
    for(int i = 0; i < candidate_count; i++){
        if(!candidates[i].eliminated){
            if(candidates[i].votes != min){
                return false;
            }
        }
    }
    return true;

}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for(int i = 0; i < candidate_count; i++){
        if(candidates[i].votes == min){
            candidates[i].eliminated = true;
        }
    }
}