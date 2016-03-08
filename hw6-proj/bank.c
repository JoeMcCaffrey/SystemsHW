#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "bank.h"
#include "command.h"
#include "errors.h"

// The account balances are represented by an array.
static int *accounts     = NULL;

// The number of accounts.
static int account_count = 0;

// The number of ATMs.
static int atm_count     = 0;

// This is used just for testing purposes.
int* get_accounts() {
  return accounts;
}

// Checks the result of a `write` call to determine if there was an
// error. If there was an error it returns ERR_PIPE_WRITE_ERR.
static int check_pipe_write(int result) {
  if (result < 0) {
    error_msg(ERR_PIPE_WRITE_ERR, "could not write to atm output file descriptor");
    return ERR_PIPE_WRITE_ERR;
  }
  else if (result < MESSAGE_SIZE) {
    error_msg(ERR_PIPE_WRITE_ERR, "partial message written to atm output file descriptor");
    return ERR_PIPE_WRITE_ERR;
  }
  else {
    return SUCCESS;
  }
}

// Checks the result of a `read` call to determine if there was an
// error. If there was an error it returns ERR_PIPE_READ_ERR.
static int check_pipe_read(int result) {
  if (result < 0) {
    error_msg(ERR_PIPE_READ_ERR, "could not read from bank input file descriptor");
    return ERR_PIPE_READ_ERR;
  }
  else if (result < MESSAGE_SIZE) {
    error_msg(ERR_PIPE_READ_ERR, "partial message read from bank input file descriptor");
    return ERR_PIPE_READ_ERR;
  }
  else {
    return SUCCESS;
  }
}

// Checks to make sure that the ATM id is a valid ID.
static int check_valid_atm(int atmid) {
  if (atmid < 0 || atmid >= atm_count) {
    error_msg(ERR_UNKNOWN_ATM, "message received from unknown ATM");
    return ERR_UNKNOWN_ATM;
  }
  else {
    return SUCCESS;
  }
}

// Checks to make sure the account ID is a valid account ID.
static int check_valid_account(int accountid) {
  if (accountid < 0 || accountid >= account_count) {
    error_msg(ERR_UNKNOWN_ACCOUNT, "message received for unknown account");
    return ERR_UNKNOWN_ACCOUNT;
  }
  else {
    return SUCCESS;
  }
}

// Opens a bank for business. It is provided the number of ATMs and
// the number of accounts.
void bank_open(int atm_cnt, int account_cnt) {
  atm_count = atm_cnt;
  // Create the accounts:
  accounts = (int *)malloc(sizeof(int) * account_cnt);
  for (int i = 0; i < account_cnt; i++)
    accounts[i] = 0;
  account_count = account_cnt;
}

// Closes a bank.
void bank_close() {
  free(accounts);
}

// Dumps out the accounts balances.
void bank_dump() {
  for (int i = 0; i < account_count; i++) {
    printf("Account %d: %d\n", i, accounts[i]);
  }
}

// The `bank` function processes commands received from an ATM. It
// processes the commands and makes the appropriate changes to the
// designated accounts if necessary. For example, if it receives a
// DEPOSIT message it will update the `to` account with the deposit
// amount. It then communicates back to the ATM with success or
// failure.
int bank(int atm_out_fd[], byte cmd[], int *atm_cnt) {
  cmd_t c;
  int i,f,t,a;
  byte bankcmd[MESSAGE_SIZE];
  cmd_unpack(cmd, &c, &i, &f, &t, &a);
  int result = SUCCESS;
//printf("atm_count1 %d\n",*atm_cnt);
  // TODO:
  // START YOUR IMPLEMENTATION

	if(check_valid_atm(i) != SUCCESS){
	result = ERR_UNKNOWN_ATM;
	return result;
	}
//printf("c = %d\n",(int)c);
	if(c == CONNECT){
//	printf("running connect\n");
	MSG_OK(bankcmd,0,f,t,a);
	result = write(atm_out_fd[i],bankcmd,MESSAGE_SIZE) ; //wierde
//	printf("result: %d\n",result);
//	printf("chekc pipe %d\n",check_pipe_write(result));
	if(check_pipe_write(result) != SUCCESS){
		result = ERR_PIPE_WRITE_ERR;
	//	printf("alkd;fjadlk;fad1\n");	
		}
	else{
	result =SUCCESS;
	
	
	}
	
	}
	else if(c == EXIT){
	//printf("EXITING BRO\n");
	*atm_cnt=(*atm_cnt)-1 ;
	MSG_OK(bankcmd,0,f,t,a);
	result = write(atm_out_fd[i],bankcmd,MESSAGE_SIZE);
	if(check_pipe_write(result) != SUCCESS){
		result= ERR_PIPE_WRITE_ERR;
		}
	
	else{
		result = SUCCESS;

	}
	}
	else if( c == DEPOSIT){
	//printf("HITTING DEPOSIT\n");
	result = check_valid_account(t);
		if(result != SUCCESS){
		//printf("BEFORE MSG ACCUNKN DEPOSIT\n");
			MSG_ACCUNKN(bankcmd,i ,t);		
			result = write(atm_out_fd[i],bankcmd,MESSAGE_SIZE);
			if(check_pipe_write(result) != SUCCESS){
				result= ERR_PIPE_WRITE_ERR;
				
		
			}
		//	else{
				
		//	result = ERR_UNKNOWN_ACCOUNT;
		
		//	}
		}
		else{
		
		result = SUCCESS;
		
	accounts[t] += a;
	MSG_OK(bankcmd,0,f,t,a);
	result= write(atm_out_fd[i],bankcmd,MESSAGE_SIZE);
		if(check_pipe_write(result) != SUCCESS){
		result = ERR_PIPE_WRITE_ERR;
		
		}
		else{
		result =SUCCESS;
		}	
	}
	}
	 else if( c == WITHDRAW){
	//printf("HITTING WITHDRAW\n");
	//result = check_valid_account(f);
		if(check_valid_account(f) != SUCCESS){
			//printf("BEFORE MSG IN WITHDRAW\n");
			MSG_ACCUNKN(bankcmd,i,f);
			result = write(atm_out_fd[i],bankcmd,MESSAGE_SIZE);
			if(check_pipe_write(result) != SUCCESS){
			result = ERR_PIPE_WRITE_ERR;
			
			}
			else{

			//result = ERR_UNKNOWN_ACCOUNT;
			result = SUCCESS;
			}
		}	
	
		else{
		result = SUCCESS;
		//here
	if( accounts[f] >=  a){
		//printf("madeit in widthdraw\n");
		accounts[f]=accounts[f]-a;//RIGHT??
		MSG_OK(bankcmd,0,f,t,a);
		result = write(atm_out_fd[i], bankcmd, MESSAGE_SIZE);
			if(check_pipe_write(result) != SUCCESS){
			
			 result = ERR_PIPE_WRITE_ERR;
			
			}	
			else{
			result = SUCCESS;
			}
		result = SUCCESS;		

	}
	else{//here
	//printf("BEFORE MSG NOFUNDS IN WIDTH\n");
	MSG_NOFUNDS(bankcmd,0,f,a);
	result= write(atm_out_fd[i],bankcmd,MESSAGE_SIZE);
		if(check_pipe_write(result) != SUCCESS){
			result= ERR_PIPE_WRITE_ERR;
			
		}
		else{
		result = SUCCESS ; // CHANGED FROM NOFUNDS
		
		}
	result = SUCCESS;// FIXED

	}
	}//change

	}	
	
	else if(c == TRANSFER){
	//printf("HITTING TRANSFER\n");
	result = check_valid_account(f);//check 1

		if(result != SUCCESS){
		//printf("BEFORE MSG TRANSFER\n");
	MSG_ACCUNKN(bankcmd,i,f);
		result = write(atm_out_fd[i],bankcmd,MESSAGE_SIZE);
			if(check_pipe_write(result) != SUCCESS){
			result = ERR_PIPE_WRITE_ERR;
			
			}
			else{

		//	result = ERR_UNKNOWN_ACCOUNT;	
			result = SUCCESS;
			}
		}
		else{
		result=SUCCESS;
		}
	result = check_valid_account(t);
		if(result != SUCCESS){ //check 2
		//printf("MSG 2 TRANSFER\n");
		MSG_ACCUNKN(bankcmd,i,t);
		result = write(atm_out_fd[i],bankcmd,MESSAGE_SIZE);
			if(check_pipe_write(result) != SUCCESS){
				result = ERR_PIPE_WRITE_ERR;
				
			}
			else{
			//result = ERR_UNKNOWN_ACCOUNT;
			result = SUCCESS;
			}
		}
		else{
		result = SUCCESS;	
		}
		
	if(a <= accounts[f]){
	accounts[t] += a;
	accounts[f] = accounts[f]-a ;
	MSG_OK(bankcmd,0,f,t,a);
	result = write(atm_out_fd[i],bankcmd,MESSAGE_SIZE);
		if(check_pipe_write(result) != SUCCESS){	
		result = ERR_PIPE_WRITE_ERR;
			

		}
		else{
		result = SUCCESS;
		}
	}
	else{
	//printf("MSG NOFUNDS\n");
	MSG_NOFUNDS(bankcmd,i,f,a);
	result = write(atm_out_fd[i],bankcmd,MESSAGE_SIZE);
		if(check_pipe_write(result) != SUCCESS){
		result = ERR_PIPE_WRITE_ERR;
			
		}
		else{
		result = SUCCESS;
		}
	//sult = NOFUNDS;
	result = SUCCESS;
	}

	}	

	else if(c == BALANCE){
	//printf("HITTING BALANCE \n");
	result = check_valid_account(f);
		if(result != SUCCESS){
		//printf("msg balance \n");
		MSG_ACCUNKN(bankcmd,i,f);
		result = write(atm_out_fd[i],bankcmd,MESSAGE_SIZE);
			if(check_pipe_write(result) != SUCCESS){
			result = ERR_PIPE_WRITE_ERR;
			
			}
			else{
			//result = ERR_UNKNOWN_ACCOUNT;
			result = SUCCESS;
			}	
		}
		else{
		result = SUCCESS;
		}
	MSG_OK(bankcmd, 0,f,t,accounts[f]);
	result = write(atm_out_fd[i],bankcmd,MESSAGE_SIZE);
		if(check_pipe_write(result) != SUCCESS){
		result = ERR_PIPE_WRITE_ERR;
		
		}
		else{
		result = SUCCESS;
		}
		
	}
	else{
	error_msg(ERR_UNKNOWN_CMD, "unknow command!!!!");
	result=	write(atm_out_fd[i],bankcmd,MESSAGE_SIZE);
		if(check_pipe_write(result) != SUCCESS){
			result = ERR_PIPE_WRITE_ERR;
			
		}
		else{
		//result=	ERR_UNKNOWN_CMD;
		result = SUCCESS;
		}
//	result = ERR_UNKNOWN_CMD;
	}
	

  // END YOUR IMPLEMENTATION

  return result;
}

int run_bank(int bank_in_fd, int atm_out_fd[]) {
  byte cmd[MESSAGE_SIZE];

  int result  = 0;
  int atm_cnt = atm_count;
  while (atm_cnt != 0) {
    result = read(bank_in_fd, cmd, MESSAGE_SIZE);
    result = check_pipe_read(result);
    if (result != SUCCESS)
      return result;

    result = bank(atm_out_fd, cmd, &atm_cnt);
    if (result != SUCCESS)
      return result;
  }

  return SUCCESS;
}
