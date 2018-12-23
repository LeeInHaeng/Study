# 메모 사항
- front-end 에서 metamask 사용하는 경우
  - web3 1.0 버전은 아직 베타 버전이기 때문에 metamask에 web3 1.0 버전이 도입되지 않음. 즉, methods를 이용하여 promise 형태의 코딩이 불가능
- back-end 에서 web3 사용하는 경우
  - web3 1.0 버전이 도입된 것이기 때문에 methods를 이용해 promise 형태로 코딩 해야됨.

# 질문 사항
- 소스 코드
  - betting.sol : 간단하게 베팅을 위한 컨트랙트 입니다. 1 또는 2 팀을 선택한 후, 베팅하는 bet 함수와 이긴 팀에게 상금을 분배하는 distributePrize 함수로 구성 됩니다.
  - views/index.ejs : front-end 페이지 입니다. 선택할 팀과 투자할 이더를 입력 후 버튼을 눌러 베팅을 합니다.
  - io.js : index.ejs 에서 버튼에 대한 이벤트가 오고, 베팅한 사람이 2명일 경우 2번 팀에게 상금을 분배 합니다.

- 여기서 질문 사항
  - 1) betting.sol에서 bet 함수의 경우에는 front-end 쪽에서 수행이 되어야 하고, distributePrize 함수의 경우에는 back-end 쪽에서 수행이 되어야 한다고 생각합니다. 하나의 contract에 이러한 식으로 front에서 수행해야 할 함수와 back에서 수행해야 할 함수가 같이 있어도 이상한 접근 방법이 아닐까요? 이를 위해 front 에서도 web3를 사용하고, back 에서도 web3를 사용해야 하는 문제가 발생 합니다.


  - 2) io.js 에서 function distributePrize 의 내용을 보시면 다음과 같은데요.
```
    function distributePrize(winnerTeam){
        return simpleBetting.methods.distributePrize(winnerTeam)
        .send({from: contractAddress });
    }
```
일단 컴파일의 경우 remix에서 ropsten 네트워크로 deploy 버튼을 눌러 컴파일을 진행했습니다.
여기서 궁금한 사항은 사용자가 bet 함수를 수행하면 컴파일 후 remix에서 제공해주는 주소로 이더를 보냅니다. 주소는 아래 사진과 같습니다.
![2](https://user-images.githubusercontent.com/20277647/50384797-44197880-070d-11e9-8747-2dafbf62b2c7.PNG)
그 후 remix에서 제공해 준 주소로부터 distributePrize를 하는 것이 맞는 방법일까요? send({from : })에 remix에서 제공해 준 주소를 사용하는 것이 맞는지 궁금합니다.

애초에 저 주소로 접근이 되지 않는 것인지, 아니면 전체적인 접근 방법이 틀린 것인지 아래와 같은 에러 메시지가 발생합니다.
![1](https://user-images.githubusercontent.com/20277647/50384719-f5b7aa00-070b-11e9-8f4c-d9a9b8c1496a.PNG)

전체적인 접근 방법 등이나 문제에 대해 조언 부탁드립니다. 감사합니다.