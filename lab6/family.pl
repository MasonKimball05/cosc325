% male facts
male(brian).
male(matthew).
male(josiah).
male(tomjr).
male(tomsr).
male(richard).
male(richardjr).

% female facts
female(analise).
female(beverly).
female(anne).
female(june).
female(kristine).
female(sharon).

% parent facts
parent(brian,josiah).
parent(brian,analise).
parent(kristine,josiah).
parent(kristine,analise).
parent(tomjr,brian).
parent(tomjr,matthew).
parent(tomsr,tomjr).
parent(richard,beverly).
parent(richard,richardjr).
parent(richard,sharon).
parent(beverly,brian).
parent(beverly,matthew).
parent(anne,tomjr).
parent(june,beverly).
parent(june,richardjr).
parent(june,sharon).

% rules
father(X, Y) :- male(X), parent(X, Y).
mother(X, Y) :- female(X), parent(X, Y).
child(X, Y) :- parent(Y, X).
son(X, Y) :- child(X, Y), male(X).
daughter(X, Y) :- child(X, Y), female(X).
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
grandfather(X, Y) :- grandparent(X, Y), male(X).
grandmother(X, Y) :- grandparent(X, Y), female(X).

sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.

% aunt(X, Y) means X is the aunt of Y
aunt(X, Y) :- female(X), sibling(X, Z), parent(Z, Y).

% uncle(X, Y) means X is the uncle of Y
uncle(X, Y) :- male(X), sibling(X, Z), parent(Z, Y).

% reverse(R, L) means R is the reversed version of L
reverse(L, R) :- reverse_acc(L, [], R).

reverse_acc([], Acc, Acc).
reverse_acc([H|T], Acc, R) :- reverse_acc(T, [H|Acc], R).