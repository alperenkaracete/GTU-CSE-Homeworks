DELIMITER //

CREATE PROCEDURE updateStaffSalaries(
    IN newSalaryRate INT
)
BEGIN
    UPDATE staff SET salary = salary + newSalaryRate*salary/100 WHERE staffID > 0;
END//

DELIMITER ;