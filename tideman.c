#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

int beat[MAX];

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
void swap_num(int a[], int x, int y);
void swap_pair(pair a[], int x, int y);
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
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(candidates[k], name) == 0)
        {
            ranks[rank] = k;
            return true;
        }
    }
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
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int n = 1;
    int strenght_pair[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        strenght_pair[i] = preferences[pairs[i].winner][pairs[i].loser];
    }
    while (n != 0)
    {
        n = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (strenght_pair[i] < strenght_pair[i + 1])
            {
                swap_num(strenght_pair, i, i + 1);
                swap_pair(pairs, i, i + 1);
                n++;
            }
        }
    }
    return;
}

//Swap two numbers in a array
void swap_num(int a[], int x, int y)
{
    int temp = a[x];
    a[x] = a[y];
    a[y] = temp;
    return;
}

//Swap two pairs in a array
void swap_pair(pair a[], int x, int y)
{
    pair temp = a[x];
    a[x] = a[y];
    a[y] = temp;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int beat_count = 0;
    for (int i = 0; i < pair_count; i++)
    {
        //Adding the arrows until there is one candidate without arrows pointed at him
        if (beat_count < candidate_count - 1)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            int n = 0;
            for (int j = 0; j < candidate_count; j++)
            {
                if (locked[j][pairs[i].loser] == true)
                {
                    n++;
                }
            }
            if (n == 1)
            {
                beat[pairs[i].loser] = 1;
                beat_count++;
            }
        }

         int secure;
        for (int x = 0; x < candidate_count; x++)
        {
            int z = 0;
            for (int y = 0; y < candidate_count; y++)
            {
                if (locked[y][x] == true)
                {
                    z++;
                }
            }
            if (z == 0)
            {
                secure = x;
            }
        }
        if (beat_count == candidate_count - 1)
        {
            if (pairs[i].loser != secure)
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (beat[i] != 1)
        {
            printf("%s\n", candidates[i]);
        }

    }
    return;
}