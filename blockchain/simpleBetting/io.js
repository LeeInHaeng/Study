module.exports = function(server){
    var io = require('socket.io')(server);
    var web3 = require('web3');
    var web3js = new web3(new web3.providers.HttpProvider("https://ropsten.infura.io/v3/1169ccd24f6843a78ba127ec9b573fc9"));
    var contractAddress = '0x9b5cc67fbb8f59800909d85807d69f0767ccb554';
    var abi = [
        {
        "constant": false,
        "inputs": [
            {
            "name": "_teamSelected",
            "type": "uint8"
            }
        ],
        "name": "bet",
        "outputs": [],
        "payable": true,
        "stateMutability": "payable",
        "type": "function"
        },
        {
        "constant": false,
        "inputs": [
            {
            "name": "_winnerTeam",
            "type": "uint16"
            }
        ],
        "name": "distributePrize",
        "outputs": [],
        "payable": false,
        "stateMutability": "nonpayable",
        "type": "function"
        },
        {
        "constant": false,
        "inputs": [],
        "name": "renounceOwnership",
        "outputs": [],
        "payable": false,
        "stateMutability": "nonpayable",
        "type": "function"
        },
        {
        "constant": false,
        "inputs": [
            {
            "name": "_minimumBet",
            "type": "uint256"
            }
        ],
        "name": "setMinimumBet",
        "outputs": [],
        "payable": false,
        "stateMutability": "nonpayable",
        "type": "function"
        },
        {
        "constant": false,
        "inputs": [
            {
            "name": "newOwner",
            "type": "address"
            }
        ],
        "name": "transferOwnership",
        "outputs": [],
        "payable": false,
        "stateMutability": "nonpayable",
        "type": "function"
        },
        {
        "inputs": [],
        "payable": false,
        "stateMutability": "nonpayable",
        "type": "constructor"
        },
        {
        "anonymous": false,
        "inputs": [
            {
            "indexed": true,
            "name": "previousOwner",
            "type": "address"
            },
            {
            "indexed": true,
            "name": "newOwner",
            "type": "address"
            }
        ],
        "name": "OwnershipTransferred",
        "type": "event"
        },
        {
        "constant": true,
        "inputs": [
            {
            "name": "_playerAddress",
            "type": "address"
            }
        ],
        "name": "checkPlayerExist",
        "outputs": [
            {
            "name": "",
            "type": "bool"
            }
        ],
        "payable": false,
        "stateMutability": "view",
        "type": "function"
        },
        {
        "constant": true,
        "inputs": [],
        "name": "getTotalBetOne",
        "outputs": [
            {
            "name": "",
            "type": "uint256"
            }
        ],
        "payable": false,
        "stateMutability": "view",
        "type": "function"
        },
        {
        "constant": true,
        "inputs": [],
        "name": "getTotalBetTwo",
        "outputs": [
            {
            "name": "",
            "type": "uint256"
            }
        ],
        "payable": false,
        "stateMutability": "view",
        "type": "function"
        },
        {
        "constant": true,
        "inputs": [],
        "name": "isOwner",
        "outputs": [
            {
            "name": "",
            "type": "bool"
            }
        ],
        "payable": false,
        "stateMutability": "view",
        "type": "function"
        },
        {
        "constant": true,
        "inputs": [],
        "name": "owner",
        "outputs": [
            {
            "name": "",
            "type": "address"
            }
        ],
        "payable": false,
        "stateMutability": "view",
        "type": "function"
        }
    ];
    var simpleBetting = new web3js.eth.Contract(abi,contractAddress);
    var userCnt = 0;

    function distributePrize(winnerTeam){
        return simpleBetting.methods.distributePrize(winnerTeam)
        .send({from: contractAddress });
    }

    io.on('connection',function(socket){
        console.log('a user socketio connected');

        socket.on('disconnect',function(){
            console.log('user disconnected');
        });

        socket.on('player wait',function(){
            userCnt+=1;
            console.log(userCnt);
            if(userCnt==2){
                distributePrize(2);
                userCnt = 0;
            }
        });
    });
    return io;
}