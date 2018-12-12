let contractAddress = '0x794adfde9c1cca5aaff6f377a474e69c2b559b86';
let abi = [
	{
		"constant": false,
		"inputs": [
			{
				"name": "candidate",
				"type": "bytes32"
			}
		],
		"name": "voteForCandidate",
		"outputs": [],
		"payable": false,
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"name": "candidateNames",
				"type": "bytes32[]"
			}
		],
		"payable": false,
		"stateMutability": "nonpayable",
		"type": "constructor"
	},
	{
		"constant": true,
		"inputs": [
			{
				"name": "",
				"type": "uint256"
			}
		],
		"name": "candidateList",
		"outputs": [
			{
				"name": "",
				"type": "bytes32"
			}
		],
		"payable": false,
		"stateMutability": "view",
		"type": "function"
	},
	{
		"constant": true,
		"inputs": [
			{
				"name": "candidate",
				"type": "bytes32"
			}
		],
		"name": "totalVotesFor",
		"outputs": [
			{
				"name": "",
				"type": "uint8"
			}
		],
		"payable": false,
		"stateMutability": "view",
		"type": "function"
	},
	{
		"constant": true,
		"inputs": [
			{
				"name": "candidate",
				"type": "bytes32"
			}
		],
		"name": "validCandidate",
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
		"inputs": [
			{
				"name": "",
				"type": "bytes32"
			}
		],
		"name": "votesReceived",
		"outputs": [
			{
				"name": "",
				"type": "uint8"
			}
		],
		"payable": false,
		"stateMutability": "view",
		"type": "function"
	}
];

let simpleVoting;
const candidates = {"Rama": "candidate-1", "Nick": "candidate-2", "Jose": "candidate-3"};

function startApp(){
    simpleVoting = web3.eth.contract(abi).at(contractAddress);
    refreshVote();
}

function refreshVote(){
    for(var i=0; i<Object.keys(candidates).length; i++){
        let name = Object.keys(candidates)[i];
        simpleVoting.totalVotesFor(name,function(e,r){
            document.getElementById(candidates[name]).innerHTML = r.toNumber();
        });
    }
}

window.addEventListener('load',function(){
    if(typeof web3 !== 'undefined'){
        this.window.web3 = new Web3(web3.currentProvider);
    }
    else{
        this.window.web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
    }
    startApp();
});

document.getElementById('voteBtn').addEventListener('click',function(e){
    let candidateName = document.getElementById("candidate").value;
    let txid;

    simpleVoting.voteForCandidate(candidateName, {from: web3.eth.accounts[0], gas:4700000}, function(e,r){
        alert(candidateName + " 에게 투표 성공!");
        refreshVote();
    });
});