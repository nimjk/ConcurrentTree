

int arr[2000];
srand(GetTrickCount());
int count = 0;
while (count < 2000)
{
    int tmp = rand() % 5000 + 1;
    int isSame = 0;
    for (int i = 0; i < 2000; i++)
    {
        if (tmp == arr[i])
        {
            isSame = 1;
            break;
        }
        if (isSame == 0)
        {
            arr[count] = tmp;
            count++;
        }
    }
    int insertcount = 0;
    while (insertcount < 2000)
    {
        new_node->value = arr[insertcount];
        obj.root = obj.insertRecursive(obj.root, new_node);
        insertcount++;
    }
}