# Created by newuser for 5.2
# Lines configured by zsh-newuser-install
setopt HIST_IGNORE_ALL_DUPS
fpath=( $fpath "$HOME/.zsh/" )
HISTFILE=~/.histfile
HISTSIZE=1000
SAVEHIST=1000
bindkey -e
# End of lines configured by zsh-newuser-install
# The following lines were added by compinstall
zstyle :compinstall filename '/home/golovanov/.zshrc'

autoload -Uz compinit
compinit

# End of lines added by compinstall

bindkey "${terminfo[khome]}" beginning-of-line
bindkey "${terminfo[kend]}" end-of-line
bindkey "${terminfo[kdch1]}" delete-char

# for prompt
autoload -Uz vcs_info

autoload -U promptinit
promptinit
prompt mine 8bit green red grey white

alias ls='ls --color=auto'
alias grep='grep --color=auto'
# alias subl='sublime'
alias python='python2'
#alias cpplint='~/distr/cpplint.py'
alias xclip='xclip -selection clipboard'
#alias sleepuntil='~/distr/sleepuntil.sh'
#alias dcj='~/distr/dcj/dcj.sh'

function agcwatch() {
	~/misc/agc_watcher/script.sh $@ > /dev/null &
}

function evnc() {
	nohup evince $@ > /dev/null
}

function beatclick() {
	~/misc/beat_clicker/beat_daemon.py $@ > /dev/null &
}
