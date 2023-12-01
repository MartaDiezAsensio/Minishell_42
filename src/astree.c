/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiez-as <mdiez-as@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:43:31 by mdiez-as          #+#    #+#             */
/*   Updated: 2023/12/01 17:15:00 by mdiez-as         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Abstract Syntax Tree

we run the array of tokens through te parser which parses it into an
abstract syntax tree.
*/

#include "../inc/minishell.h"

void	tree_attach_branch(t_tree_node *root, t_tree_node *left, t_tree_node *right)
{
	if (!root)
		return ;
	root->left = left;
	root->right = right;
}

void	tree_node_set_type(t_tree_node *node, node_type type)
{
	if (!node)
		return ;
	node->type = type;
}

void	tree_node_set_data(t_tree_node *node, char *data)
{
	if (!node)
		return ;
	if (data != NULL)
	{
		node->sz_data = ft_strdup(data);
		node->type |= NODE_DATA;
	}
}

void	tree_node_delete(t_tree_node *node)
{
	if (node == NULL)
		return ;
	if (node->type & NODE_DATA)
		free(node->sz_data);
	tree_node_delete(node->left);
	tree_node_delete(node->right);
	free(node);
}

/************************************************************************/

// int main()
// {
// 	t_tree_node	*root;
// 	t_tree_node	*left_child;
// 	t_tree_node	*right_child;

// 	root = malloc(sizeof(t_tree_node));
// 	if (!root)
// 		return (1);
	
// 	left_child = malloc(sizeof(t_tree_node));
// 	if (!left_child)
// 		return (1);
// 	right_child = malloc(sizeof(t_tree_node));
// 	if (!right_child)
// 		return (1);
	
// 	// Attach branches
// 	tree_attach_branch(root, left_child, right_child);

// 	// Set types and data
// 	tree_node_set_type(root, NODE_PIPE);
// 	tree_node_set_type(left_child, NODE_SEQ);
// 	tree_node_set_type(right_child, NODE_ARGUMENT);

// 	tree_node_set_data(root, "|");
// 	tree_node_set_data(left_child, "echo");
// 	tree_node_set_data(right_child, "hello");

// 	// Display node types and data
// 	printf("Root type: %d and data: %s\n", NODE_TYPE(root->type), root->sz_data);
// 	printf("Left type: %d and data: %s\n", NODE_TYPE(left_child->type), left_child->sz_data);
// 	printf("Right type: %d and data: %s\n", NODE_TYPE(right_child->type), right_child->sz_data);
	
// 	//Delete nodes
// 	tree_node_delete(root);

// 	return (0);
// }
