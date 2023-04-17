
% knowledge base

schedule(canakkale,erzincan,6).
schedule(erzincan,antalya,3).
schedule(antalya,izmir,2).
schedule(antalya,diyarbakir,4).
schedule(izmir,ankara,6).
schedule(izmir,istanbul,2). 
schedule(istanbul,ankara,1).
schedule(istanbul,rize,4). 
schedule(diyarbakir,ankara,8).
schedule(ankara,rize,5).
schedule(ankara,van,4).
schedule(van,gaziantep,3).
schedule(diyarbakir,gaziantep,3). % new added.
schedule(ankara,antalya,7). % new added.

% reverse connections

schedule(diyarbakir,antalya,4).
schedule(izmir,antalya,2).
schedule(antalya,erzincan,3).
schedule(istanbul,izmir,2). 
schedule(rize,ankara,5).
schedule(ankara,izmir,6).
schedule(ankara,diyarbakir,8).
schedule(ankara,istanbul,1).
schedule(rize,istanbul,4).
schedule(van,ankara,4).
schedule(gaziantep,van,3).
schedule(erzincan,canakkale,6).
schedule(gaziantep,diyarbakir,3). % new added.
schedule(antalya,ankara,7). % new added.

% rules 

connection(X,Y,C) :- 
  
  X \== Y,
  connection(X,Y,C,[]).

connection(X,Y,C,VisitedCities) :- 
  
  schedule(X,NewCity,Distance1), 
  not(member(NewCity,VisitedCities)), % if NewCity is not in the list of VisitedCities, then assign .
  append([NewCity], VisitedCities, NewVisitedCities), % Add new city to start of the list.
  ((Y = NewCity, C is Distance1); 
  (connection(NewCity,Y,Distance2,NewVisitedCities),C is Distance2 + Distance1)). % Addded Distance1 and Distance2 and assing it to C.