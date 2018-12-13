pragma solidity ^0.5.1;

contract Converter{
    function stringToBytes32(string memory source)view public returns (bytes32 result) {
        bytes memory tempEmptyStringTest = bytes(source);
        if (tempEmptyStringTest.length == 0) {
            return 0x0;
        }
    
        assembly {
            result := mload(add(source, 32))
        }
    }
}

// stringToBytes32(hello)