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
}
pair;

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
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate name matches, set rank appropriately based on candidate index
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    // Reached end of array without finding voter
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // So this works like a box with a divider line:
    // boxes with X will never be greater than zero so skip
    // +-+-+-+
    // |X| | |
    // +-----+
    // | |X| |
    // +-----+
    // | | |X|
    // +-+-+-+


    // Start at second row, and only check values to left of dividing line
    for (int row = 1; row < candidate_count; row++)
    {
        // Only need to check to before the dividing line
        for (int col = 0; col < row; col++)
        {
            int rowCandidateVictories = preferences[row][col];
            int colCandidateVictories = preferences[col][row];

            if (rowCandidateVictories == colCandidateVictories)
            {
                continue;
            }

            int winningCandidateIndex = rowCandidateVictories > colCandidateVictories ? row : col;
            int losingCandidateIndex = winningCandidateIndex == row ? col : row;

            pair pair = {winningCandidateIndex, losingCandidateIndex};
            pairs[pair_count] = pair;
            pair_count++;
        }
    }
    return;
}

void sort(int array[][])
{
    mergeSort(array, 0, sizeof(array) - 1);
}

void mergeSort(int array[][], int leftIndex, int rightIndex)
{

}

void merge()
{

}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{   // Initialize strength count based on pairs (determines the win counts)
    // first value is pair index
    // second value is win count
    int strength_count[pair_count][pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        strength_count[i][0] = i;
        strength_count[i][1] = preferences[pairs[i].winner][pairs[i].loser];
    }

    // Sort the pairs based on strength (using merge sort modified to use 2d array)
    // TODO
    // I'm planning to merge sort a modified array that holds the original pair index

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

