/**************************************************************************************************/
/* Copyright (C) mc2lab.com, SSE@USTC, 2014-2015                                                  */
/*                                                                                                */
/*  FILE NAME             :  menu.c                                                               */
/*  PRINCIPAL AUTHOR      :  Mengning                                                             */
/*  SUBSYSTEM NAME        :  menu                                                                 */
/*  MODULE NAME           :  menu                                                                 */
/*  LANGUAGE              :  C                                                                    */
/*  TARGET ENVIRONMENT    :  ANY                                                                  */
/*  DATE OF FIRST RELEASE :  2014/09/22                                                           */
/*  DESCRIPTION           :  Interface of the menu                                                */
/**************************************************************************************************/

/*
 * Revision log:
 *
 * Created by Mengning, 2014/09/22
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "linktable.h"
#include "menu.h"



#define CMD_MAX_LEN 128
#define DESC_LEN    1024
#define CMD_NUM     10

/* data struct and its operations */

tLinkTable * front = NULL;

/* find a cmd in the linklist and return the datanode pointer */
tDataNode* FindCmd(char * cmd)
{
    tDataNode * pNode = (tDataNode*)GetLinkTableHead(front);
    while(pNode != NULL)
    {
        if(!strcmp(pNode->cmd, cmd))
        {
            return  pNode;  
        }
        pNode = (tDataNode*)GetNextLinkTableNode(front,(tLinkTableNode *)pNode);
    }
    return NULL;
}

/* show all cmd in listlist */
int ShowAllCmd()
{
    tDataNode * pNode = (tDataNode*)GetLinkTableHead(front);
    printf("Menu List:\n");
    while(pNode != NULL)
    {
        printf("%s - %s\n", pNode->cmd, pNode->desc);
        pNode = (tDataNode*)GetNextLinkTableNode(front,(tLinkTableNode *)pNode);
    }
    return 0;
}

/* Inite menu date */
int InitMenuData(tMenuNode * data)
{
    tLinkTable *ppLinktable = CreateLinkTable();
    front = ppLinktable;
    while(data != NULL)
    {
        tDataNode* pNode = (tDataNode*)malloc(sizeof(tDataNode));
        pNode->cmd = data->cmd;
        pNode->desc = data->desc;
    	pNode->handler = data->handler;
    	AddLinkTableNode(ppLinktable,(tLinkTableNode *)pNode);
    	data = data->next;
    }
    return 0; 
}

/* Add menu Node */ 
int AddMenuNode(tMenuNode * menuNode)
{
    tDataNode* pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = menuNode->cmd;
    pNode->desc = menuNode->desc;
   	pNode->handler = menuNode->handler;
   	AddLinkTableNode(front,(tLinkTableNode *)pNode);
	tDataNode * p = FindCmd(menuNode->cmd);
	if(p)
	{
 	 	printf("Create menu success!\n");
    }
	else
	{
		 printf("Create menu Failure!\n");
	}
	return 0;	
}

/* Add menu Node */ 
int DeleteMenuNode(char * cmd)
{
     tDataNode * p = FindCmd(cmd);
	 if(p == NULL)
     {
         printf("Not having this cmd!\n");
         return 0;
	 }
	 int flag = DelLinkTableNode(front,(tLinkTableNode *)p);   
	 if(!flag)
	 {
	     printf("Delete Menu Success!\n");
	 }
	 else
	 {
         printf("Delete Menu Failure!\n");
	 }	
	 return 0;
}

