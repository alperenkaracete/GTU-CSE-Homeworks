% knowledge base
:-dynamic(room/3).
:-dynamic(course/6).
:-dynamic(instructor/3).
:-dynamic(student/3).
:-dynamic(roomoccupy/3).

% Room id,capacity,roomequipments
room(a,80,projector).
room(b,90,smartboard).
room(c,100,projector).

% Course id,capacity,instructor,hour,room,handicap if handicap is 1 its mean that if student has handicap,student can not enroll to this course. 
course(cse101,70,mehmet,4,a,0).
course(cse241,100,sinan,2,a,1).
course(cse341,75,yakup,2,b,1).

% Instructor id,course id,courserequirement
instructor(mehmet,cse101,smartboard).
instructor(sinan,cse241,projector).
instructor(yakup,cse341,projector).

% Student id,course id,handicap
student(alperen,cse341,0).
student(abdullah,cse241,0).
student(fazil,[cse241, cse341],1).
student(mert,[cse101, cse241],1).

roomoccupy(room1,8,cse101).
roomoccupy(room1,9,cse101).
roomoccupy(room1,13,cse241).
roomoccupy(room1,14,cse241).
roomoccupy(room2,15,cse341).
roomoccupy(room2,16,cse341).
roomoccupy(room3,11,cse101).
roomoccupy(room3,12,cse101).

% add room
add_room(Id,Capacity,Equipment) :-
	\+ room(Id, _, _),
	assert(room(Id, Capacity, Equipment)).

% add course
add_course(Id, Capacity, Instructor, Hour, Room, Handicap) :-
	\+ course(Id, _, _, _, _, _),
	assert(course(Id, Capacity, Instructor, Hour, Room, Handicap)).

% add instructor
add_instructor(Id, Course, Equipment):-
	\+ instructor(Id, _, _),
	assert(instructor(Id, Course, Equipment)).    

% add student
add_student(Id, Course, Handicap):-
	\+ student(Id, _, _),
	assert(student(Id, Course, Handicap)).

% Queries:

% Check is there any scheduling conflict.
check_conflict(Course1, Course2) :-
	roomoccupy(Room1,Time1,Course1),
    roomoccupy(Room2,Time2,Course2),
    Course1 \==  Course2,  % If course is not the same course and time and room number is equal to enother class, then this means there is conflict.
    Time1 == Time2,
    Room1 == Room2,
    format('Conflict found!~n').

% Check room and course match.
check_course_can_assign_room(RoomId,CourseId) :-
    
    room(RoomId,RoomCapacity,RoomEquipments),
    course(CourseId, CourseCapacity, InstructorId, _, _,_),
    instructor(InstructorId,_,CourseRequirements),
    RoomCapacity >= CourseCapacity,  % If room capacity is bigger or equal to student count and room requirement can meet the course rqeuirement than course can assign to the room.
    RoomEquipments = CourseRequirements,
    format('Course can be assigned to room this room!').
    
% Check student enroll
check_can_student_enroll_class(StudentId,CourseId):-
    student(StudentId,_,SHandicap),
    course(CourseId,_,_,_,_,CHandicap),
    CHandicap = 1,  % Course has handicap, so if a student has handicap student can not enroll to class.
    SHandicap = 0,
    format('Student can be enrolled to class ~n').

