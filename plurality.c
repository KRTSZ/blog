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
    //checking initial values
    printf("%s \n", argv[0]);
    printf("%i \n", argc);
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
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    // TODO
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winnerCount = 0;
    string winner[MAX];
    winner[winnerCount] = candidates[0].name;
    int winning_votes = candidates[0].votes;
    for (int i = 0; i < MAX; i ++)
    {
        if (candidates[i].votes == winning_votes)
        {
            winnerCount += 1;
            winner[winnerCount] = candidates[i].name;
        }

        if (candidates[i].votes > winning_votes)
        {
            winning_votes = candidates[i].votes;
            //set new winner
            winnerCount = 0;
            winner[winnerCount] = candidates[i].name;
        }

    }


    for(int a = 0; a <= winnerCount; a++)
    {
        printf("The winner is %s.\n", winner[a]);
    }
    // TODO
    return;
}

