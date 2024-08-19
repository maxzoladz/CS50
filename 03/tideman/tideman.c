#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool isCycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for(int candidate = 0; candidate < candidate_count; candidate++) {

        if(strcmp(name, candidates[candidate]) == 0) {
            ranks[rank] = candidate;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int rank_above = 0; rank_above < candidate_count; rank_above++) {
        for(int rank_below = rank_above + 1; rank_below < candidate_count; rank_below++) {
            preferences[ranks[rank_above]][ranks[rank_below]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for(int candidate_a = 0; candidate_a < candidate_count; candidate_a++) {
        for(int candidate_b = candidate_a + 1; candidate_b < candidate_count; candidate_b++) {
            if(preferences[candidate_a][candidate_b] > preferences[candidate_b][candidate_a]) {
                pairs[pair_count].winner = candidate_a;
                pairs[pair_count].loser = candidate_b;
                pair_count++;
            }
            else if(preferences[candidate_a][candidate_b] < preferences[candidate_b][candidate_a]) {
                pairs[pair_count].winner = candidate_b;
                pairs[pair_count].loser = candidate_a;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for(int outerCounter = 0; outerCounter < pair_count; outerCounter++) {
        for(int innerCounter = 0; innerCounter < pair_count - outerCounter; innerCounter++) {
            int strengthCurrentPair = preferences[pairs[innerCounter].winner][pairs[innerCounter].loser];
            int strengthNextPair = preferences[pairs[innerCounter + 1].winner][pairs[innerCounter + 1].loser];

            if(strengthCurrentPair < strengthNextPair) {
                pair temporaryPair = pairs[innerCounter];
                pairs[innerCounter] = pairs[innerCounter + 1];
                pairs[innerCounter + 1] = temporaryPair;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int pairIndex = 0; pairIndex < pair_count; pairIndex++) {
        bool cycleExists = isCycle(pairs[pairIndex].winner, pairs[pairIndex].loser);

        if(!cycleExists) {
            locked[pairs[pairIndex].winner][pairs[pairIndex].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    for(int counter = 0; counter < candidate_count; counter++) {
        bool winner = true;

        for(int innerCounter = 0; innerCounter < candidate_count; innerCounter++) {
            if(locked[innerCounter][counter]){
                winner = false;
                break;
            }
        }

        if(winner == true) {
            printf("Winner: %s\n", candidates[counter]);
        }
        
    }

    return;
}

bool isCycle(int winner, int loser) {
    if(winner == loser) {
        return true;
    }

    for(int pairIndex = 0; pairIndex < candidate_count; pairIndex++){
        if(locked[loser][pairIndex]) {
            if(isCycle(winner, pairIndex)) return true;
        }
    }

    return false;
}


