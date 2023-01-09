CLIENT_DIR=./client
SERVER_DIR=./server

CLIENT_BIN=tcp_client
SERVER_BIN=tcp_server

CP=cp

all: client server

client:
	$(MAKE) -sC ${CLIENT_DIR}
	$(CP) $(CLIENT_DIR)/$(CLIENT_BIN) .

server:
	$(MAKE) -sC ${SERVER_DIR}
	$(CP) $(SERVER_DIR)/$(SERVER_BIN) .

clean:
	$(MAKE) -sC ${CLIENT_DIR} clean
	$(MAKE) -sC ${SERVER_DIR} clean

fclean:
	$(MAKE) -sC ${CLIENT_DIR} fclean
	$(MAKE) -sC ${SERVER_DIR} fclean
	$(RM) $(CLIENT_BIN)
	$(RM) $(SERVER_BIN)

re: fclean all

.PHONY: all client server clean fclean re
