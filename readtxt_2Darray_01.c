String input = File.ReadAllText( @"c:\myfile.txt" );

int i = 0, j = 0;
int[,] result = new int[10, 10];
foreach (var row in input.Split('\n'))
{
    j = 0;
    foreach (var col in row.Trim().Split(' '))
    {
        result[i, j] = int.Parse(col.Trim());
        j++;
    }
    i++;
}