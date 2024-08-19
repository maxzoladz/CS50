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
} candidate;

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
    for (int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++)
    {
        candidates[candidateIndex].name = argv[candidateIndex + 1];
        candidates[candidateIndex].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int candidateIndex = 0; candidateIndex < voter_count; candidateIndex++)
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
bool vote(string name)
{
    for(int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++) {
        bool nameIsCandidate = strcmp(name, candidates[candidateIndex].name) == 0;
        if(nameIsCandidate) {
            candidates[candidateIndex].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int highestVotes = 0;

    for(int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++) {
        if(candidates[candidateIndex].votes > highestVotes) {
            highestVotes = candidates[candidateIndex].votes;
        }
    }

    for(int candidateIndex = 0; candidateIndex < candidate_count; candidateIndex++) {
        if(candidates[candidateIndex].votes == highestVotes) {
            printf("Winner: %s\n", candidates[candidateIndex].name);
        }
    }

    return;
}