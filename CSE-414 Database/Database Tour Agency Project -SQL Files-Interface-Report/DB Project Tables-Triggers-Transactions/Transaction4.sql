DELIMITER //

CREATE PROCEDURE updateCustomerName(
    IN tempCustomerID INT,
		newName VARCHAR(255)
)
BEGIN
    UPDATE customer SET custName = newName WHERE custID = tempCustomerID;
END//

DELIMITER ;