#!/bin/bash

# Gera um nome de sessão único usando timestamp
SESSION_NAME="sync_session_$(date +%s)"

# Se já estiver no tmux
if [ -n "$TMUX" ]; then
    echo "Você já está em uma sessão tmux. Criando nova sessão aninhada..."

    # Desconecta de outras sessões antes de criar uma nova
    tmux new-session -d -s $SESSION_NAME -n "main" bash

    # Divide o painel verticalmente
    tmux split-window -h -t $SESSION_NAME

    # Inicia o bash no novo painel
    tmux send-keys -t $SESSION_NAME "bash" C-m

    # Ativa a sincronização de painéis
    tmux set-window-option -t $SESSION_NAME synchronize-panes on

    # Anexa à nova sessão interna
    tmux attach-session -t $SESSION_NAME

else
    # Se não estiver em uma sessão tmux, cria uma nova sessão externa
    tmux new-session -d -s $SESSION_NAME -n "main" bash

    # Divide o painel verticalmente
    tmux split-window -h -t $SESSION_NAME

    # Inicia o bash no novo painel
    tmux send-keys -t $SESSION_NAME "bash" C-m

    # Ativa a sincronização de painéis
    tmux set-window-option -t $SESSION_NAME synchronize-panes on

    # Anexa à sessão para o usuário interagir
    tmux attach-session -t $SESSION_NAME
fi
