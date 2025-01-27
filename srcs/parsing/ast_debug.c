/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebugle <llebugle@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:20:05 by llebugle          #+#    #+#             */
/*   Updated: 2025/01/27 20:20:07 by llebugle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ast_debug.c */
#include "ast.h"

// Helper function to get node content as a string
static char *get_node_str(t_ast_node *node)
{
    static char buf[1024];  // Static buffer for the string
    t_command *cmd;
    int i;

    if (!node)
        return ("NULL");

    if (node->type == NODE_PIPE)
        return ("PIPE");
    
    cmd = (t_command *)node->data;
    buf[0] = '\0';
    strcat(buf, "CMD[");
    for (i = 0; i < cmd->arg_count; i++)
    {
        strcat(buf, cmd->args[i]);
        if (i < cmd->arg_count - 1)
            strcat(buf, " ");
    }
    strcat(buf, "]");
    return (buf);
}

// Print indentation
static void print_indent(int level)
{
    for (int i = 0; i < level; i++)
        printf("  ");
}

// Function to assign unique IDs to nodes
static int assign_node_ids(t_ast_node *root, int *id)
{
    int current_id;

    if (!root)
        return (-1);

    current_id = (*id)++;
    root->id = current_id;  // You'll need to add 'id' field to t_ast_node
    assign_node_ids(root->left, id);
    assign_node_ids(root->right, id);
    return (current_id);
}

void print_node_relationships(t_ast_node *node, int level)
{
    if (!node)
        return;

    print_indent(level);
    printf("Node %d: %s\n", node->id, get_node_str(node));
    
    print_indent(level);
    printf("├── Left Child : %s (Node %d)\n", 
           node->left ? get_node_str(node->left) : "NULL",
           node->left ? node->left->id : -1);
    
    print_indent(level);
    printf("└── Right Child: %s (Node %d)\n", 
           node->right ? get_node_str(node->right) : "NULL",
           node->right ? node->right->id : -1);
    
    printf("\n");

    if (node->left)
        print_node_relationships(node->left, level + 1);
    if (node->right)
        print_node_relationships(node->right, level + 1);
}

void print_detailed_ast(t_ast_node *root)
{
    int id = 0;

    printf("\nDetailed AST Structure:\n");
    printf("=====================\n\n");
    
    // First assign IDs to all nodes
    assign_node_ids(root, &id);
    
    // Then print the relationships
    print_node_relationships(root, 0);
}

static void print_node_content(t_ast_node *node)
{
    int i;

    if (node->type == NODE_PIPE)
        printf("PIPE");
    else if (node->type == NODE_COMMAND)
    {
        t_command *cmd = (t_command *)node->data;
        printf("CMD[");
        for (i = 0; i < cmd->arg_count; i++)
        {
            printf("%s", cmd->args[i]);
            if (i < cmd->arg_count - 1)
                printf(" ");
        }
        printf("]");
    }
}

// Pre-order traversal (Root -> Left -> Right)
void print_preorder(t_ast_node *node)
{
    if (!node)
        return;

    print_node_content(node);
    printf(" -> ");
    print_preorder(node->left);
    print_preorder(node->right);
}

// In-order traversal (Left -> Root -> Right)
void print_inorder(t_ast_node *node)
{
    if (!node)
        return;

    print_inorder(node->left);
    print_node_content(node);
    printf(" -> ");
    print_inorder(node->right);
}

// Post-order traversal (Left -> Right -> Root)
void print_postorder(t_ast_node *node)
{
    if (!node)
        return;

    print_postorder(node->left);
    print_postorder(node->right);
    print_node_content(node);
    printf(" -> ");
}

// Print all traversals
void print_all_traversals(t_ast_node *root)
{
    printf("\nTraversal Orders:\n");
    printf("-----------------\n");
    
    printf("Pre-order  : ");
    print_preorder(root);
    printf("END\n");
    
    printf("In-order   : ");
    print_inorder(root);
    printf("END\n");
    
    printf("Post-order : ");
    print_postorder(root);
    printf("END\n");
    printf("-----------------\n");
}