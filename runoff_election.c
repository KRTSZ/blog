#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
string preferences[MAX_VOTERS][MAX_CANDIDATES];

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
        printf("Maximum number of candidates is %i.\n", MAX_CANDIDATES);
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
        printf("Maximum number of voters is %i.\n", MAX_VOTERS);
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
        //printf("tabulate\n");
        tabulate();

        // Check if election has been won
        //printf("winner\n");
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        //printf("min\n");
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        //printf("tie\n");
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
        //printf("elimnate\n");
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
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = name;
            return true;
        }
    }
    // TODO
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    //set all candidate votes to zero
    for (int a = 0; a < candidate_count; a++)
    {
        candidates[a].votes = 0;
    }
    //printf("set zero\n");

    //count the highest ranked candidate of each voter as vote
    for (int j = 0; j < voter_count; j++)
    {
        int k = 0;
        while (k < candidate_count)
        {

            for (int i = 0; i < candidate_count; i++)
            {
                if ((candidates[i].eliminated == false) && (strcmp(preferences[j][k], candidates[i].name) == 0))                    {
                    candidates[i].votes += 1;
                    //printf("break %i.\n", i);
                    break;
                }
            }
            k++;
            break;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        //printf("candidate %s has %i votes.\n", candidates[i].name, candidates[i].votes);
    }
    // TODO
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int total_votes = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        total_votes += candidates[i].votes;
    }
    //printf("total votes %i.\n", total_votes);

    for (int a = 0; a < candidate_count; a++)
    {
        if (candidates[a].votes > (total_votes/2.0))
        {
            printf("The winner is %s.\n", candidates[a].name);
            return true;
        }
    }
    // TODO
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].eliminated == false) && (candidates[i].votes < min))
        {
            min = candidates[i].votes;
        }
    }
    //printf("min = %i.\n", min);
    // TODO
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes > min)
        {
            //printf("tie false.\n");
            return false;
        }
    }
    // TODO
    printf("This is a tie between:\n");
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }

        // TODO
    }
    return;
}
