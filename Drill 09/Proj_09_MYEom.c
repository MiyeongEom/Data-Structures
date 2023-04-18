#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct DSongNode {
	element sName;
	struct DSongNode* llink;
	struct DSongNode* rlink;
}DSongNode;

typedef struct DPlaylistNode {	// 이중연결 노드 타입
	element pName;
	struct DPlaylistNode* llink;
	struct DPlaylistNode* rlink;
	struct DSongNode* slink;
} DPlaylistNode;


void print_aPlaylist(DPlaylistNode* head, DPlaylistNode* current)
{
	DPlaylistNode* p = head;

	if (p == NULL) {
		printf("Playlist : %s\n", p->pName);
		return;
	}

	printf("Playlist : ");
	while (p->rlink != head) {
		if (p == current) printf("<-[*%s*]-> ", p->pName);
		else printf("<-[%s]-> ", p->pName);
		p = p->rlink;
	}
	if (p == current) printf("<-[*%s*]-> ", p->pName);
	else printf("<-[%s]-> ", p->pName);
	printf("\n");
}

void insert_nPlaylist(DPlaylistNode** head, element data, DPlaylistNode** current)
{
	DPlaylistNode* p = *head;

	DPlaylistNode* newnode = (DPlaylistNode*)malloc(sizeof(DPlaylistNode));
	strcpy(newnode->pName, data);
	newnode->llink = NULL;
	newnode->rlink = NULL;
	newnode->slink = NULL;
	*current = newnode;

	if (*head == NULL) {
		*head = newnode;
		(*head)->rlink = newnode;
		(*head)->llink = newnode;
	}
	else {
		while (p->rlink != *head) {
			p = p->rlink;
		}
		newnode->rlink = *head;
		newnode->llink = p;
		p->rlink = newnode;
		(*head)->llink = newnode;
	}
}

void delete_cPlaylist(DPlaylistNode** head, DPlaylistNode** current)
{
	DPlaylistNode* tmp = *current;

	// 우선 삭제 
	if (tmp->slink != NULL) {
		DSongNode* p = tmp->slink;
		DSongNode* q;
		while (p->rlink != tmp->slink) {
			q = p;
			p = p->rlink;
			free(q);
			q = NULL;
		}
		free(p);
	}

	if (tmp->rlink == tmp && tmp->llink == tmp) { 
		*current = NULL;
		*head = NULL;
	}
	else {
		tmp->llink->rlink = tmp->rlink;
		tmp->rlink->llink = tmp->llink;
		*current = tmp->rlink;
		if (*head == tmp) *head = *current;
	}

	free(tmp);
	tmp = NULL;
}

void change_cPlaylist(DPlaylistNode** current, int dir)
{
	if (dir == 1) { 
		*current = (*current)->rlink;
	}
	else { 
		*current = (*current)->llink;

	}
	return;
}

void insert_nSongList(DPlaylistNode* playlist, element song, DSongNode** current)
{
	DSongNode* p = playlist->slink;
	DSongNode* newnode = NULL;

	newnode = (DSongNode*)malloc(sizeof(DSongNode));
	strcpy(newnode->sName, song);
	newnode->rlink = NULL;
	newnode->llink = NULL;
	*current = newnode;

	if (p == NULL) {
		playlist->slink = newnode;
		newnode->rlink = newnode;
		newnode->llink = newnode;
	}
	else {
		while (p->rlink != playlist->slink) {
			p = p->rlink;
		}
		newnode->rlink = playlist->slink;
		newnode->llink = p;
		p->rlink = newnode;
		playlist->slink->llink = newnode;
	}
}


void delete_cSong(DPlaylistNode* pl, DSongNode** cur)
{
	DSongNode* tmp = *cur;

	if (tmp->llink == tmp && tmp->rlink == tmp) { 
		pl->slink = NULL;
		free(tmp);
		*cur = NULL;
		tmp = NULL;
	}
	else {
		*cur = tmp->rlink;
		tmp->llink->rlink = tmp->rlink;
		tmp->rlink->llink = tmp->llink;
		if (pl->slink == tmp) { 
			pl->slink = *cur;
		}
		free(tmp);
		tmp = NULL;
	}
}

void change_cSong(DSongNode** current, int dir)
{
	if (dir == 1) {
		*current = (*current)->rlink;
	}
	else { 
		*current = (*current)->llink;
	}
	return;
}

void print_aSong(DPlaylistNode* playlist, DSongNode* current)
{
	DSongNode* p = playlist->slink;

	if (p == NULL) {
		printf("Song list : %s\n", p->sName);
		return;
	}

	printf("Song list : ");
	while (p->rlink != playlist->slink) {
		if (p == current) printf("<-[*%s*]-> ", p->sName);
		else printf("<-[%s]-> ", p->sName);
		p = p->rlink;
	}
	if (p == current) printf("<-[*%s*]-> ", p->sName);
	else printf("<-[%s]-> ", p->sName);
	printf("\n");
}

void print_playlist_menu(void)
{
	printf("\n\n---- Playlist Menu ---- \n");
	printf(" a : print all playlist \n");
	printf(" c : print current playlist\n");
	printf(" n : new playlist \n");
	printf(" d : delete playlist \n");
	printf(" > : next playlist \n");
	printf(" < : previous playlist \n");
	printf(" s : song menu \n");
	printf(" q : quit \n");
	return;
}

void print_song_menu(void)
{
	printf("\n\n---- Song Menu ---- \n");
	printf(" a : print all songs \n");
	printf(" c : print current song\n");
	printf(" n : add new song in playlist \n");
	printf(" d : delete current song \n");
	printf(" > : next song \n");
	printf(" < : previous song \n");
	printf(" b : quit \n");
	return;
}


int main(void)
{
	DPlaylistNode* head = NULL;
	element buf;
	DPlaylistNode* currentPlaylist = NULL;
	DSongNode* currentSong = NULL;
	char menu, sub_menu;
	do {
		//printf("메뉴 선택");
		print_playlist_menu();
		printf("\nSelect Menu : ");
		scanf(" %c", &menu);
		printf("--------------------------\n");
		printf("Selected playlist menu : %c \n", menu);
		switch (menu) {
		case 'a':
			print_aPlaylist(head, currentPlaylist);
			break;
		case 'c':
			printf("Current playlist : %s\n", currentPlaylist->pName);
			break;
		case 'n':
			printf("Playlist name : ");
			scanf("%s", buf);
			insert_nPlaylist(&head, buf, &currentPlaylist);
			print_aPlaylist(head, currentPlaylist);
			break;
		case 'd':
			delete_cPlaylist(&head, &currentPlaylist);
			print_aPlaylist(head, currentPlaylist);
			break;
		case '<':
			change_cPlaylist(&currentPlaylist, 2);
			print_aPlaylist(head, currentPlaylist);
			break;
		case '>':
			change_cPlaylist(&currentPlaylist, 1);
			print_aPlaylist(head, currentPlaylist);
			break;
		case 's':
			currentSong = currentPlaylist->slink;
			do {
				printf("Cur PL : %s, Cur Song : %s \n", currentPlaylist->pName, currentSong->sName);
				print_song_menu();
				printf("Select Menu : ");
				scanf(" %c", &sub_menu);
				printf("Selected song menu : %c \n", sub_menu);
				switch (sub_menu) {
				case 'a':
					print_aSong(currentPlaylist, currentSong);
					break;
				case 'c':
					printf("current song : %s\n", currentSong->sName);
					break;
				case 'n':
					printf("Song name : ");
					scanf("%s", buf);
					insert_nSongList(currentPlaylist, buf,
						&currentSong);
					print_aSong(currentPlaylist, currentSong);
					break;
				case 'd':
					delete_cSong(currentPlaylist, &currentSong);
					print_aSong(currentPlaylist, currentSong);
					break;
				case '<':
					change_cSong(&currentSong, 2);
					print_aSong(currentPlaylist, currentSong);
					break;
				case '>':
					change_cSong(&currentSong, 1);
					print_aSong(currentPlaylist, currentSong);
					break;
				}
			} while (sub_menu != 'b');
			break;
		}
	} while (menu != 'q');
	return 0;
}