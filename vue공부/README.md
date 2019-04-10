# 공부 URL
- https://kr.vuejs.org/v2/guide/index.html
- https://velopert.com/vuejs-tutorials

# 선언적 렌더링
- 선언적으로 DOM에 데이터 렌더링
  - el : 어떤 엘리먼트에 적용할 지 정한다.
  - data : 해당 뷰에서 사용할 정보를 지닌다.
  - app.message 등으로 data 안의 요소에 접근하여 동적으로 변경할 수 있다.
```
    <div id="app">
        {{ message }}
    </div>

        var app = new Vue({
            el: '#app',
            data: {
                message: '안녕하세요 Vue!'
            }
        })
```

# 디렉티브 (지시문)
- ```v-``` 접두어가 붙어 있으며 렌더링 된 DOM에 특수한 반응형 동작을 한다.
- v-once : 엘리먼트 안의 데이터 변경 시 업데이트가 되지 않는다.
```
<span v-once>다시는 변경하지 않습니다: {{ msg }}</span>
```
- v-html : 일반 텍스트가 아닌 실제 HTML로 해석하여 적용
  - 해당 디렉티브 사용시 XSS 취약점에 노출될 수 있기 때문에 주의해서 사용할 필요가 있다.
```
<p>Using mustaches: {{ rawHtml }}</p>
<p>Using v-html directive: <span v-html="rawHtml"></span></p>

            data: {
                rawHtml: '<span style="color:red">This should be red</span>'
            }
```
- v-bind : 엘리먼트 안의 속성 값을 Vue를 통해 동적으로 컨트롤 하기 위해 사용
```
        <div v-bind:id="dynamicId"></div>
        <button v-bind:disabled="isButtonDisabled">Button</button>

            data: {
                dynamicId: 'myDynamicID',
                isButtonDisabled: false
            }
```
- v-show : 해당 엘리먼트를 보여줄지 말지를 지정할 수 있다.
```
        <p v-show="isMyVisible">보이나요?</p>

            data: {
                isMyVisible: true
            }
```
- v-if : 조건문 로직을 수행하기 위해 사용한다.
  - v-if, v-else-if, v-else 구문으로 수행
  - 만약 하나 이상의 엘리먼트를 보여주고 싶은 경우 template 으로 묶는다.
  - template의 경우에도 마찬가지로 if, else-if, else 구문을 사용할 수 있다.
```
        <p v-if="myVal > 5">값이 5보다 커요</p>
        <p v-else-if="myVal === 5">값이 5에요</p>
        <p v-else>값이 5보다 작아요</p>

            data: {
                myVal : 4
            }

	// template
        <template v-if="myVal > 5">
            <p>엘리먼트1</p>
            <p>엘리먼트2</p>
            <p>엘리먼트3</p>
        </template>
```
- v-pre : 해당 엘리먼트부터 자식 엘리먼트까지 지시문이 없다는 것을 알림으로써 컴파일 속도를 빠르게 한다.
  - 첫 번째 msg는 머스태시 태그까지 그대로 출력, 두 번째 msg는 변수에 설정된 값 적용
```
        <div v-pre>{{ 머스태시 태그가 그대로 출력되요 }}
            <p>{{ msg }}</p>
        </div>
        <p>{{ msg }}</p>

            data: {
                msg: '머스태시 태그가 그대로 출력 되나요?'
            }
```
- v-for : 반복문을 통해 엘리먼트를 그려주기 위한 지시문
  - 오브젝트 타입의 경우에도 반복문을 사용할 수 있다.
```
            <li v-for="(todo, idx) in todos">
                {{ idx }} {{ todo.text }}
            </li>

            data: {
                todos: [
                    {text : 'Javascript 배우기'},
                    {text : 'Vue 배우기'},
                    {text : '무언가 만들기'}
                ]
            }

// 오브젝트 타입

        <ul>
            <li v-for="(val, key, idx) in obj">
                {{idx}} : {{key}} : {{val}}
            </li>
        </ul>

            data: {
                obj: {
                    firstName : 'John',
                    lastName : 'Doe',
                    age : 30
                }
            }
```
- v-model : 양방향 바인딩을 위한 지시문
  - 기존에는 엘리먼트 선언 후, JS에서 변경해 값을 변경해주면 엘리먼트에 적용되는 방식 이었는데, 엘리먼트에서 값을 변경하면 JS의 값도 변경 되도록 바인딩
  - 폼 input이나 textarea 등의 양방향 데이터 바인딩을 위해 사용
  - input 값을 변경하면 실시간으로 name이 변경된다.
  - 그 외에 체크, 라디오, 셀렉트 등에서 선택된 항목의 value를 바로 얻어올 수 있다.
```
        <p>Model Test! {{ name }}</p>
        <input type="text" v-model="name"/>

            data: {
                name : 'Hello Vue!'
            }
```
- v-model 체크, 라디오, 셀렉트 예시
```
        <input type="checkbox" value="Jack" v-model="checkedName">
        <input type="checkbox" value="John" v-model="checkedName">
        <input type="checkbox" value="Mike" v-model="checkedName">
        <span>{{ checkedName }}</span>
        <br/>
        
        <input type="radio" value="One" v-model="picked">
        <input type="radio" value="Two" v-model="picked">
        <span>{{ picked }}</span>
        <br/>
        
        <select v-model="selected" multiple>
            <option>A</option>
            <option>B</option>
            <option>C</option>
        </select>
        <span>{{ selected }}</span>
        <br/>
        
        <select v-model="selected2">
            <option v-for="op in options" v-bind:value="op.value">
                {{ op.text }}
            </option>
        </select>
        <span>{{ selected2 }}</span>

            data: {
                checkedName: [],
                picked: '',
                selected: [],
                selected2: '',
                options: [
                    {text: 'One', value: 'A'},
                    {text: 'Two', value: 'B'},
                    {text: 'Three', value: 'C'}
                ]
            }
```
- v-on : 엘리먼트에 이벤트를 적용하기 위한 지시문
  - v-on:이벤트이름="메소드이름" 형식으로 작성
  - Vue 객체 안의 methods에서 함수 작성
```
        <p>카운터 : {{ cnt }}</p>
        <button v-on:click="doSomething1">1씩 증가</button>
        <button v-on:click="doSomething2(cnt)">cnt씩 증가</button>

            data: {
                cnt: 0
            },
            methods: {
                doSomething1: function(){
                    this.cnt++;
                },
                doSomething2: function(paramCnt){
                    this.cnt += paramCnt;
                }
            }
```

# computed 속성
- computed 속성 : 어떠한 로직 처리를 위해 함수화 하여 사용하는 것
- 겉 모습으로 computed 속성과 methods 속성은 동일하게 동작한다.
- 둘의 차이점은 computed 속성은 종속 대상에 의존하여 캐싱되기 때문에 종속된 대상이 변경될 때만 해당 함수를 수행한다.
- 즉, 종속된 대상이 변경되지 않는다면 해당 함수를 여러번 호출해도 다시 계산하지 않고, 계산되어 있던 결과를 즉시 반환 한다는 장점이 있다.
- 단점은 어떠한 데이터에도 종속되지 않는다면 해당 함수를 아무리 호출해도 업데이트 되지 않을 수 있기 때문에 주의해서 사용할 필요가 있다. (ex : Date.now() )
- computed 속성은 매개변수를 직접 전달하지 않고, function 안에서 처리한다.
```
// message 데이터에 종속

        <p>methods속성 : {{ reversedMessage1() }}</p>
        <p>computed속성 : {{ reversedMessage2 }}</p>

            data: {
                message: '겉모습은 같아요'
            },
            methods: {
                reversedMessage1: function(){
                    return this.message.split('').reverse().join('')
                }
            },
            computed: {
                reversedMessage2: function(){
                    return this.message.split('').reverse().join('')
                }
            }
```
- computed 속성에서 필요한 경우 setter 함수 또한 구현할 수 있다.
```
        <p>computed속성 setter 테스트 : {{ fullName }}</p>

            data: {
                firstName : 'Foo',
                lastName : 'Bar'
            },
            computed: {
                fullName: {
                    get: function(){
                        return this.firstName + ' ' + this.lastName
                    },
                    set: function(newName){
                        var names = newName.split(' ')
                        this.firstName = names[0]
                        this.lastName = names[names.length-1]
                    }
                }
            }
        app12.fullName = 'In Haeng'
```

# HTML 클래스 바인딩
- 기본적으로 v-bind:class 를 이용하여 바인딩 한다.
- 일반 class 속성과 공존할 수 있다.
```
        <div class="static" 
             v-bind:class="{'active' : isActive, 'text-danger' : hasError}">
        클래스 바인딩
        </div>

            data: {
                isActive: true,
                hasError: false
            }

// 결과 : <div class="static active">
```
- 엘리먼트에 배열 형태로 키 값을 셋팅한 후 Vue에서 벨류를 통해 클래스를 셋팅할 수도 있다.
```
<div v-bind:class="[activeClass, errorClass]"></div>

data: {
  activeClass: 'active',
  errorClass: 'text-danger'
}

// 결과 : <div class="active text-danger"></div>
```
- style을 바인딩 할 수 있다.
  - 숫자의 경우 따옴표를 함께 사용해야 한다는 점에 주의할 필요가 있다.
```
<div v-bind:style="{ color: activeColor, fontSize: fontSize + 'px' }"></div>

data: {
  activeColor: 'red',
  fontSize: 30
}
```
- 여러 값을 배열로 전달하는 경우 (2.3 버전 이상)
```
<div v-bind:style="{ display: ['-webkit-box', '-ms-flexbox', 'flex'] }"></div>
```

# data의 배열 변경 감지
- data에 배열을 추가하는 경우 : push를 사용한다.
- data의 길이를 변경해야 하는 경우 : splice를 사용한다.
```
            data: {
                todos: [
                    {text : 'Javascript 배우기'},
                    {text : 'Vue 배우기'},
                    {text : '무언가 만들기'}
                ]
            }

// 추가
app8.todos.push({ text: 'New item' })
// 추가(methods 안에서)
this.todos.splice(index, 0, value)

// length 변경
app8.todos.splice(newLength)

// 삭제(methods 안에서)
this.todos.splice(index, 1)
```

- 오브젝트의 값을 변경하거나, 추가하는 경우 : Vue.set을 사용한다.
```
var vm = new Vue({
  data: {
    userProfile: {
      name: 'Anika'
    }
  }
})

// 변경하는 경우
Vue.set(vm.userProfile, name, 'InHaeng')

// 추가하는 경우
Vue.set(vm.userProfile, 'age', 27)

// 반응형이 지원되지 않는 추가 (권장하지 않음)
vm.userProfile2 = 'hihi'
```

- 필터링을 사용하여 배열을 얻고 싶은 경우 : filter을 사용한다.
  - methods 속성과 computed 속성은 햇깔리므로 주의해서 사용할 필요가 있다.
```
        <ul>
            <li v-for="n in evenMethods(numbers)">{{ n }}</li>
        </ul>
        <ul>
            <li v-for="n in evenComputed">{{ n }}</li>
        </ul>

            data: {
                numbers: [1,2,3,4,5]
            },
            methods: {
                evenMethods: function(myNum){
                    return myNum.filter(function(num){
                        return num % 2 === 0
                    })
                }
            },
            computed:{
                evenComputed: function(){
                    return this.numbers.filter(function(num){
                        return num % 2 === 0
                    })
                }
            }
```

# 이벤트 핸들링
- https://kr.vuejs.org/v2/guide/events.html
- 방지 이벤트들
- v-on:click.prevent.self : 모든 클릭 방지
- v-on:click.self.prevent : 엘리먼트 자체에 대한 클릭만 방지합니다.
```
<!-- 클릭 이벤트 전파가 중단됩니다 -->
<a v-on:click.stop="doThis"></a>

<!-- 제출 이벤트가 페이지를 다시 로드 하지 않습니다 -->
<form v-on:submit.prevent="onSubmit"></form>

<!-- 수식어는 체이닝 가능합니다 -->
<a v-on:click.stop.prevent="doThat"></a>

<!-- 단순히 수식어만 사용할 수 있습니다 -->
<form v-on:submit.prevent></form>

<!-- 이벤트 리스너를 추가할 때 캡처모드를 사용합니다 -->
<!-- 즉, 내부 엘리먼트를 대상으로 하는 이벤트가 해당 엘리먼트에서 처리되기 전에 여기서 처리합니다. -->
<div v-on:click.capture="doThis">...</div>

<!-- event.target이 엘리먼트 자체인 경우에만 트리거를 처리합니다 -->
<!-- 자식 엘리먼트에서는 안됩니다 -->
<div v-on:click.self="doThat">...</div>

<!-- 클릭 이벤트는 최대 한번만 트리거 됩니다. -->
<a v-on:click.once="doThis"></a>

<!-- 스크롤의 기본 이벤트를 취소할 수 없습니다. -->
<div v-on:scroll.passive="onScroll">...</div>
```
- 마우스, 키보드 키 관련 이벤트들
```
<!-- keyCode가 13일 때만 `vm.submit()`을 호출합니다  -->
<input v-on:keyup.13="submit">

<!-- Alt(Ctrl, Shift) + C -->
<input v-on:keyup.alt.67="clear">

<!-- Ctrl(Alt, Shift) + Click -->
<div v-on:click.ctrl="doSomething">Do something</div>

<!-- Ctrl 키만 눌려있을 때만 실행됩니다. -->
<button v-on:click.ctrl.exact="onCtrlClick">A</button>

<!-- 아래 코드는 시스템 키가 눌리지 않은 상태인 경우에만 작동합니다. -->
<button v-on:click.exact="onClick">A</button>

click.left
click.right
click.middle
```
