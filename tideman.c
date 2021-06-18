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
    //printf("vote\n");
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {

            ranks[rank] = i;
            //printf("%s true \n", name);
            return true;
        }
    }// TODO
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //int a = 0;
    //int b = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = (i + 1); j < candidate_count; j++)
        {
            int r = 0;
            while(r < candidate_count)
            {
                if (i == j)
                {
                    break;
                }
                if (ranks[r] == i)
                {
                    preferences[i][j] += 1;
                    break;
                }
                if (ranks[r] == j)
                {
                    preferences[i][j] -= 1;

                    break;
                }
                r++;
            }
        }
    }
    //int c = preferences[i][j];
    //printf("%i over %i by %i\n", i, j, a);
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //printf("add sorted pairs\n");
    int p = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > p)
            {
                p = preferences[i][j];
            }
        }
    }
    //printf("max %i\n", p);
    for (int difference = p; difference > 0; difference--)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                if ((preferences[i][j] == difference) && (i != j))
                {
                    pairs[p].winner = i;
                    pairs[p].loser = j;
                    //printf("winner %i, loser %i, margin %i\n", pairs[p].winner, pairs[p].loser, preferences[i][j]);
                    p++;
                }
            }
        }
    }
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //printf("lock pairs\n");
    int upper = candidate_count * (candidate_count - 1) /2;
    for (int p = 0; p <= upper; p++)
    {
        bool a = false;
        bool b = false;
        if (pairs[p].winner == pairs[p].loser)
        {
            a = true;
            b = true;
            //printf("same pair %i/%i\n", pairs[p].winner, pairs[p].loser);
        }
        for(int d = 0; d < upper; d++)
        {

            if (locked[d][pairs[p].loser] == true)
            {
                a = true;
            }
            if (locked[pairs[p].winner][d] == true)
            {
                b = true;
            }
        }
        if ((a == true) && (b == true))
        {
            //circular
            locked[pairs[p].winner][pairs[p].loser] = false;
            //printf("circular pair %i/%i\n", pairs[p].winner, pairs[p].loser);
        }
        else
        {
            locked[pairs[p].winner][pairs[p].loser] = true;
            //printf("locked pair %i/%i\n", pairs[p].winner, pairs[p].loser);
        }
    }
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //printf("print winner\n");
    int upper = candidate_count * (candidate_count - 1) / 2;
    for (int p = 0; p <= upper; p++)
    {
        bool a = false;
        bool b = false;
        for(int i = 0; i < candidate_count; i++)
        {
            if (locked[i][pairs[p].winner] == true)
            {
                a = true;
                //printf("a = true\n");
            }
            if (locked[pairs[p].winner][i] == true)
            {
                b = true;
                //printf("b = true\n");
            }
        }
        if ((a == false) && (b == true))
        {
            printf("The winner is %s.\n", candidates[pairs[p].winner]);
            break;
        }
        else
        {
            //printf("something wrong\n");
        }
    }

    // TODO
    return;
}
