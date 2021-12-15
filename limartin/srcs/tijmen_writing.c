#include "ColdRace.h"

typedef struct s_substr
{
    char *str;
    int len;
    struct s_substr *next;
}   t_substr;


t_substr *lst_add(char *str, int len)
{
    t_substr *link;

    link = malloc(sizeof(t_substr));
    if (!link)
        return NULL;
    link->str = str;
    link->len = len;
    return (link);
}

void writeOutput(t_substr *root, int strLen)
{
    char *output;
    t_substr *link;
    int outputIndex = 0;
    int substringIndex;

    output = malloc(sizeof(char) * (strLen + 1));
    if (!output)
        return;
    link = root;
    while (link)
    {
        substringIndex = 0;
        while (substringIndex < link->len)
        {
            output[outputIndex + substringIndex] = link->str[substringIndex];
            substringIndex++;
        }
        outputIndex += substringIndex;
        link = link->next;
    }
	output[strLen] = '\0';
    write(1, output, strLen);
}

void resolve_queries(t_ht *ht)
{
    char *value;
    char *line = 0;
    t_substr root;
    t_substr *link;
    char nl[] = "\n";
    char notfound[] = ": Not found.\n";
    int strLen = 0;
	int len = 0;
	int query_len;

    link = &root;
    while (get_next_line(0, &line))
    {
        if (line[0] == '\0')
            break;
        value = ht_retrieve(ht, line, &len);
        if (value == NULL)
        {
			query_len = ft_strlen(line);
            link->next = lst_add(line, query_len);
            link = link->next;
            link->next = lst_add(notfound, 13);
            link = link->next;
            strLen += query_len + 13;
        }
        else
        {
            link->next = lst_add(value, len);
            link = link->next;
            link->next = lst_add(nl, 1);
            link = link->next;
            strLen += len + 1;
        }
    }
	if (line[0] != '\0')
	{
        value = ht_retrieve(ht, line, &len);
        if (value == NULL)
        {
			query_len = ft_strlen(line);
            link->next = lst_add(line, query_len);
            link = link->next;
            link->next = lst_add(notfound, 13);
            link = link->next;
            strLen += query_len + 13;
        }
        else
        {
            link->next = lst_add(value, len);
            link = link->next;
            link->next = lst_add(nl, 1);
            link = link->next;
            strLen += len + 1;
        }
	}
    link->next = NULL;
    writeOutput((root.next), strLen);
}

int hybrid_write_values(t_ht *ht)
{
	int ret = 1;
	char *query_key;
	char *query_value;
	int query_len = 0;
	int val_len = 0;
    char nl[] = "\n";
    char notfound[] = ": Not found.\n";
    int strLen = 0;
    t_substr root;
    t_substr *link;
	link = &root;

	while(ret)
	{
		ret = get_next_line(0, &query_key);
		query_len = ft_strlen(query_key);
		if (query_len == 0)
			break;

        query_value = ht_retrieve(ht, query_key, &val_len);
        if (query_value == NULL)
        {
            link->next = lst_add(query_key, query_len);
            link = link->next;
            link->next = lst_add(notfound, 13);
            link = link->next;
            strLen += query_len + 13;
        }
        else
        {
            link->next = lst_add(query_value, val_len);
            link = link->next;
            link->next = lst_add(nl, 1);
            link = link->next;
            strLen += val_len + 1;
        }
	}
	link->next = NULL;
    writeOutput((root.next), strLen);
	return (0);
}