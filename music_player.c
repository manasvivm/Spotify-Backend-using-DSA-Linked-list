#include "queue.h"
#include "dll.h"
#include "music_player.h"
#include <stdio.h>
#include <stdlib.h>

playlist_t* create_playlist() // return a newly created doubly linked list
{
	// DO NOT MODIFY!!!
	playlist_t* playlist = (playlist_t*) malloc(sizeof(playlist_t));
	playlist->list = create_list();
	playlist->num_songs = 0;
	playlist->last_song = NULL;
	return playlist;
}

void delete_playlist(playlist_t* playlist) // delete the playlist
{
	// DO NOT MODIFY!!!
	delete_list(playlist->list);
	free(playlist);
}

music_queue_t* create_music_queue() // return a newly created queue
{
	// DO NOT MODIFY!!!
	return create_queue();
}

void clear_music_queue(music_queue_t* q) // clear the queue q
{	
	// DO NOT MODIFY!!!
	delete_queue(q);
}

void add_song(playlist_t* playlist, int song_id, int where) // TODO: add a song id to the end of the playlist
{  song_t* temporary=(song_t*)malloc(sizeof(song_t));
   temporary->data=song_id;
   temporary->prev=temporary->next=NULL;
	if (where==-1)
	{
		
		if (playlist->list->head==NULL)
		{
			playlist->list->head=temporary;
			playlist->list->size++;
			playlist->num_songs++;
		}
		else
		{
			temporary->next=playlist->list->head;
			playlist->list->head->prev=temporary;
			playlist->list->head=temporary;
			playlist->list->size++;
			playlist->num_songs++;
		}
		song_t* current=playlist->list->head;
		song_t* prev=NULL;
		while(current!=NULL)
		{
			prev=current;
			current=current->next;
		}
		playlist->list->tail=prev;
		
		return;
   }
   
   else if(where==-2)
   {
   		if (playlist->list->head==NULL)
		{
			playlist->list->head=temporary;
			playlist->list->size++;
			playlist->num_songs++;
			return ;
   		}
		else
		{
			song_t* current=playlist->list->head;
			song_t* prev=NULL;
			while(current!=NULL)
			{
				prev=current;
				current=current->next;
			}
			playlist->list->tail=prev;
			playlist->list->tail->next=temporary;
			temporary->prev=playlist->list->tail;
			playlist->list->tail=temporary;
			playlist->list->size++;
			playlist->num_songs++;
			return;
		}
	}
	
	else if(where>0)
	{
		
		song_t* current=search_song(playlist,where);
		if (current==NULL)
		{
			return;
		}
		else
		{
			if (current->next!=NULL)
			{
				song_t* second=current->next;
				temporary->next=second;
				temporary->prev=current;
				current->next=temporary;
				second->prev=temporary;
			}
			else
			{
				current->next=temporary;
				temporary->prev=current;
				playlist->list->tail=temporary;
			}
		}
		playlist->list->size++;
		playlist->num_songs++;
		

		return ;
	}
	else
	{
		return ;
	}
}

void delete_song(playlist_t* playlist, int song_id) // TODO: remove song id from the playlist
{
	if (playlist->list->size==0)
	{
		return;
	}
	else
	{
		song_t* current=search_song(playlist,song_id);
		if (current==NULL)
		{
			return ;
		}
		else
		{
			if (playlist->last_song==current) playlist->last_song=NULL;
			if (current->prev==NULL)
			{
					song_t* current=playlist->list->head;
					song_t* second=current->next;
				if (second==NULL)
				{
					playlist->list->head=playlist->list->tail=NULL;
					free(current);
					current=NULL;
				}
				else
				{
					playlist->list->head=second;
					second->prev=NULL;
					free(current);
					current=NULL;
				}
			}
			
			
			else if(current->next==NULL)
			{
				
				if(playlist->list->size==1)
				{
				   playlist->list->head=playlist->list->tail=NULL;
				}
				else
				{
					song_t* last=playlist->list->tail;
					song_t* secend=last->prev;
					playlist->list->tail=secend;
					secend->next=NULL;
					free(last);
					last=NULL;
				}	
			}
			else
			{
					song_t* before =current->prev;
					before->next=current->next;
					current->next->prev=before;
					free(current);
					current=NULL;
			}
		}
		playlist->list->size--;  
		playlist->num_songs--;
		
		return ;
	}
}

song_t* search_song(playlist_t* playlist, int song_id) // TODO: return a pointer to the node where the song id is present in the playlist
{
	song_t* found=playlist->list->head;
	while(found!=NULL)
	{
		if(found->data==song_id)
			return found;
		found=found->next;
	}
	return NULL;
}

void search_and_play(playlist_t* playlist, int song_id) // TODO: play the song with given song_id from the list(no need to bother about the queue. Call to this function should always play the given song and further calls to play_next and play_previous)
{
	song_t* current=search_song(playlist,song_id);
	playlist->last_song=current;
	if (current==NULL) 
	{
		return;
	}
	play_song(song_id);
	return ;
}

void play_next(playlist_t* playlist, music_queue_t* q) // TODO: play the next song in the linked list if the queue is empty. If the queue if not empty, play from the queue
{
	if (q->front==NULL)
	{
		if (playlist->last_song==NULL || playlist->last_song->next==NULL)
		{
			playlist->last_song=playlist->list->head;
			play_song(playlist->last_song->data);
		}
		else
		{
			playlist->last_song=playlist->last_song->next;
			play_song(playlist->last_song->data);
		}
	 return ;   
	}
	else if(q->front!=NULL)
	{
		play_from_queue(q);
	}
	else return ;
}

void play_previous(playlist_t* playlist) // TODO: play the previous song from the linked list
{
	if(playlist->list->head!=NULL)
	{
		if (playlist->last_song==NULL || playlist->last_song->prev==NULL)
		{
			playlist->last_song=playlist->list->tail;
			play_song(playlist->last_song->data);
		}
		else
		{
			playlist->last_song=playlist->last_song->prev;
		   play_song(playlist->last_song->data);
		}
		return ;
	}
	else 
	{
		return ;
	}
}

void play_from_queue(music_queue_t* q) // TODO: play a song from the queue
{
	int x=dequeue(q);
	play_song(x);
}

void insert_to_queue(music_queue_t* q, int song_id) // TODO: insert a song id to the queue
{
	enqueue(q,song_id);
	
}

void reverse(playlist_t* playlist) // TODO: reverse the order of the songs in the given playlist. (Swap the nodes, not data)
{  
	if (playlist->list->head==NULL) return ;
	else{
		song_t* temporary=playlist->list->head;
		song_t* temporaryo=NULL;
		song_t* current=temporary;
		song_t* prevn=NULL;
		
		while(temporary->next!=NULL)
		{
			current=temporary->next;
			temporary->next=temporary->prev;
			temporary->prev=current;
			prevn=temporary;
			temporary=current;
			current=current->next;
			
			
		}
		temporary->next=prevn;
		temporary->prev=NULL;
		
		temporaryo=playlist->list->head;
		playlist->list->head=playlist->list->tail;
		playlist->list->tail=temporaryo;
		return;
	}
	
	
}

void k_swap(playlist_t* playlist, int k) // TODO: swap the node at position i with node at position i+k upto the point where i+k is less than the size of the linked list
{   
    if(playlist->list->size!=0){
	int n=playlist->num_songs;
	int i=0;
	song_t* temporary=playlist->list->head;
	song_t* current= playlist->list->head;
	for (i=0;i+k<n;i++)
	{
		current=temporary;
		
		for(int y=0;y<k;y++)
		{
			current=current->next;
		}
		song_t* currentn= current->next;
		song_t* currentp= current->prev;
		song_t* temporaryn=temporary->next;
		song_t* temporaryp=temporary->prev;
		if(k==1)
		{
			currentp=current;
			temporaryn=temporary;
		}
		
		current->next=temporaryn;
		current->prev=temporaryp;
		temporary->next=currentn;
		temporary->prev=currentp;
		if (temporaryn!=NULL) temporaryn->prev=current;
		if (currentn!=NULL) currentn->prev=temporary;
		if (currentp!=NULL) currentp->next=temporary;
		
		if (temporary==playlist->list->head)
		{
			playlist->list->head=current;
			
		}
		else
		{
			temporaryp->next=current;
		}
		 //display_playlist(playlist);
		 temporary=temporaryn;
		
	}
   
   song_t* last=playlist->list->head;
   song_t* slast=NULL;
   while(last!=NULL)
   {
	   slast=last;
	   last=last->next;
   }
   playlist->list->tail=slast;
}}

void shuffle(playlist_t* playlist, int k) // TODO: perform k_swap and reverse
{
	k_swap(playlist,k);
	reverse(playlist);
}

song_t* debug(playlist_t* playlist) // TODO: if the given linked list has a cycle, return the start of the cycle, else return null. Check cycles only in forward direction i.e with the next pointer. No need to check for cycles in the backward pointer.
{
	song_t* current=playlist->list->tail->next;
	return current;
	
}

void display_playlist(playlist_t* p) // Displays the playlist
{
	// DO NOT MODIFY!!!
	display_list(p->list);
	
}

void play_song(int song_id)
{
	// DO NOT MODIFY!!!
	printf("Playing: %d\n", song_id);
}

