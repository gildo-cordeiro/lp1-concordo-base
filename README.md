Discente: Gildo Cordeiro Duarte - 20190146782

## Para compilar

```console
make
```

## Para executar
Você pode rodar o sistema e em logo depois digitar os comandos seguidos de ENTER
```console
./main
```

Ou pode criar um arquivo de texto com uma lista de comandos (um por linha) e executar o sistema redirecionando esse arquivo como entrada padrão:
```console
./concordo < script_comandos.txt
```

## Estrutura
Os arquivos `.cpp`, `.hpp` e `.o` ficam armazenados em src, include e bin, respectivamente. O makefile se encarrega de criar a pasta bin e jogar os compilaveis la dentro e em seguida recuperar essas arquivos e gerar o executavel `main` na estrutura raiz do projeto.

## Entrada e Saida
Segue abaixo alguns exemplos de entradas e saidas corretas. O sistema poderá retornar uma saida diferente a depender da entrada informada. 

OBS.: os "<>" indicam um parâmetro `<Nome Sobrenome> = Gildo Cordeiro`

1. `comando create-user`
```console
input: create-user <nome.sobrenome@email.com.br> <senha_qualquer> <Nome Sobrenome>
output: "Usuário criado"
```

2. `comando login`
```console
input: login <nome.sobrenome@email.com.br> <senha_qualquer>
output: "Usuário criado"
```

3. `comando disconnect`
```console
input: disconnect
output: "Desconectando <nome.sobrenome@email.com.br>"
```

4. `comando create-server`
```console
input: create-server <meu_server>
output: "Servidor criado"
```

5. `comando set-server-desc`
```console
input: set-server-desc <meu_server> <"Essa mensagem descreve meu servidor">
output: "Descrição do servidor <meu_server> modificada!"
```

6. `comando set-server-invite-code`
```console
input: set-server-invite-code <meu_server> <codigo>
output: Código de convite do servidor <meu_server> modificado!
```

7. `comando set-server-invite-code`
```console
input: set-server-invite-code <meu_server> <codigo>
output: Código de convite do servidor <meu_server> modificado!
```

8. `comando list-servers`
```console
input: list-servers
output: é retornada uma lista com os servidores...
```

9. `comando remove-server`
```console
input: remove-server <meu_server>
output: "Servidor <meu_server> removido"
```

10. `comando enter-server`
```console
input: enter-server <meu_server>
output: "Entrou no servidor com sucesso"
```

11. `comando leave-server`
```console
input: leave-server
output: "Saindo do servidor <meu_server>"
```

12. `comando list-participants`
```console
input: list-participants
output: é retornada uma lista de com os participantes do servidor...
```

13. `comando list-channels`
```console
input: list-channels
output: é retornada uma lista de com os canais de texto e de voz...
```

14. `comando create-channel`
```console
input: create-channel <nome_canal> <tipo_canal>
output: "Canal de <tipo_canal> <nome_canal> criado"
```

15. `comando enter-channel`
```console
input: enter-channel <nome_canal>
output: "Entrou no canal <nome_canal>"
```

16. `comando leave-channel`
```console
input: leave-channel
output: "Saindo do canal"
```

17. `comando send-message`
```console
input: send-message <"Essa é uma mensagem">
output: null
```

18. `comando list-messages`
```console
input: list-messages
output: <Nome Sobrenome> <[data_hora_envio_mensagem]> ": Essa é uma mensagem 1" 
output: <Nome Sobrenome> <[data_hora_envio_mensagem]> ": Essa é uma mensagem 2"
output: <Nome Sobrenome> <[data_hora_envio_mensagem]> ": Essa é uma mensagem 3"  
```
