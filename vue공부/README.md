# ���� URL
- https://kr.vuejs.org/v2/guide/index.html
- https://velopert.com/vuejs-tutorials

# ������ ������
- ���������� DOM�� ������ ������
  - el : � ������Ʈ�� ������ �� ���Ѵ�.
  - data : �ش� �信�� ����� ������ ���Ѵ�.
  - app.message ������ data ���� ��ҿ� �����Ͽ� �������� ������ �� �ִ�.
```
    <div id="app">
        {{ message }}
    </div>

        var app = new Vue({
            el: '#app',
            data: {
                message: '�ȳ��ϼ��� Vue!'
            }
        })
```

# ��Ƽ�� (���ù�)
- ```v-``` ���ξ �پ� ������ ������ �� DOM�� Ư���� ������ ������ �Ѵ�.
- v-once : ������Ʈ ���� ������ ���� �� ������Ʈ�� ���� �ʴ´�.
```
<span v-once>�ٽô� �������� �ʽ��ϴ�: {{ msg }}</span>
```
- v-html : �Ϲ� �ؽ�Ʈ�� �ƴ� ���� HTML�� �ؼ��Ͽ� ����
  - �ش� ��Ƽ�� ���� XSS ������� ����� �� �ֱ� ������ �����ؼ� ����� �ʿ䰡 �ִ�.
```
<p>Using mustaches: {{ rawHtml }}</p>
<p>Using v-html directive: <span v-html="rawHtml"></span></p>

            data: {
                rawHtml: '<span style="color:red">This should be red</span>'
            }
```
- v-bind : ������Ʈ ���� �Ӽ� ���� Vue�� ���� �������� ��Ʈ�� �ϱ� ���� ���
```
        <div v-bind:id="dynamicId"></div>
        <button v-bind:disabled="isButtonDisabled">Button</button>

            data: {
                dynamicId: 'myDynamicID',
                isButtonDisabled: false
            }
```
- v-show : �ش� ������Ʈ�� �������� ������ ������ �� �ִ�.
```
        <p v-show="isMyVisible">���̳���?</p>

            data: {
                isMyVisible: true
            }
```
- v-if : ���ǹ� ������ �����ϱ� ���� ����Ѵ�.
  - v-if, v-else-if, v-else �������� ����
  - ���� �ϳ� �̻��� ������Ʈ�� �����ְ� ���� ��� template ���� ���´�.
  - template�� ��쿡�� ���������� if, else-if, else ������ ����� �� �ִ�.
```
        <p v-if="myVal > 5">���� 5���� Ŀ��</p>
        <p v-else-if="myVal === 5">���� 5����</p>
        <p v-else>���� 5���� �۾ƿ�</p>

            data: {
                myVal : 4
            }

	// template
        <template v-if="myVal > 5">
            <p>������Ʈ1</p>
            <p>������Ʈ2</p>
            <p>������Ʈ3</p>
        </template>
```
- v-pre : �ش� ������Ʈ���� �ڽ� ������Ʈ���� ���ù��� ���ٴ� ���� �˸����ν� ������ �ӵ��� ������ �Ѵ�.
  - ù ��° msg�� �ӽ��½� �±ױ��� �״�� ���, �� ��° msg�� ������ ������ �� ����
```
        <div v-pre>{{ �ӽ��½� �±װ� �״�� ��µǿ� }}
            <p>{{ msg }}</p>
        </div>
        <p>{{ msg }}</p>

            data: {
                msg: '�ӽ��½� �±װ� �״�� ��� �ǳ���?'
            }
```
- v-for : �ݺ����� ���� ������Ʈ�� �׷��ֱ� ���� ���ù�
  - ������Ʈ Ÿ���� ��쿡�� �ݺ����� ����� �� �ִ�.
```
            <li v-for="(todo, idx) in todos">
                {{ idx }} {{ todo.text }}
            </li>

            data: {
                todos: [
                    {text : 'Javascript ����'},
                    {text : 'Vue ����'},
                    {text : '���� �����'}
                ]
            }

// ������Ʈ Ÿ��

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
- v-model : ����� ���ε��� ���� ���ù�
  - �������� ������Ʈ ���� ��, JS���� ������ ���� �������ָ� ������Ʈ�� ����Ǵ� ��� �̾��µ�, ������Ʈ���� ���� �����ϸ� JS�� ���� ���� �ǵ��� ���ε�
  - �� input�̳� textarea ���� ����� ������ ���ε��� ���� ���
  - input ���� �����ϸ� �ǽð����� name�� ����ȴ�.
  - �� �ܿ� üũ, ����, ����Ʈ ��� ���õ� �׸��� value�� �ٷ� ���� �� �ִ�.
```
        <p>Model Test! {{ name }}</p>
        <input type="text" v-model="name"/>

            data: {
                name : 'Hello Vue!'
            }
```
- v-model üũ, ����, ����Ʈ ����
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
- v-on : ������Ʈ�� �̺�Ʈ�� �����ϱ� ���� ���ù�
  - v-on:�̺�Ʈ�̸�="�޼ҵ��̸�" �������� �ۼ�
  - Vue ��ü ���� methods���� �Լ� �ۼ�
```
        <p>ī���� : {{ cnt }}</p>
        <button v-on:click="doSomething1">1�� ����</button>
        <button v-on:click="doSomething2(cnt)">cnt�� ����</button>

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

# computed �Ӽ�
- computed �Ӽ� : ��� ���� ó���� ���� �Լ�ȭ �Ͽ� ����ϴ� ��
- �� ������� computed �Ӽ��� methods �Ӽ��� �����ϰ� �����Ѵ�.
- ���� �������� computed �Ӽ��� ���� ��� �����Ͽ� ĳ�̵Ǳ� ������ ���ӵ� ����� ����� ���� �ش� �Լ��� �����Ѵ�.
- ��, ���ӵ� ����� ������� �ʴ´ٸ� �ش� �Լ��� ������ ȣ���ص� �ٽ� ������� �ʰ�, ���Ǿ� �ִ� ����� ��� ��ȯ �Ѵٴ� ������ �ִ�.
- ������ ��� �����Ϳ��� ���ӵ��� �ʴ´ٸ� �ش� �Լ��� �ƹ��� ȣ���ص� ������Ʈ ���� ���� �� �ֱ� ������ �����ؼ� ����� �ʿ䰡 �ִ�. (ex : Date.now() )
- computed �Ӽ��� �Ű������� ���� �������� �ʰ�, function �ȿ��� ó���Ѵ�.
```
// message �����Ϳ� ����

        <p>methods�Ӽ� : {{ reversedMessage1() }}</p>
        <p>computed�Ӽ� : {{ reversedMessage2 }}</p>

            data: {
                message: '�Ѹ���� ���ƿ�'
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
- computed �Ӽ����� �ʿ��� ��� setter �Լ� ���� ������ �� �ִ�.
```
        <p>computed�Ӽ� setter �׽�Ʈ : {{ fullName }}</p>

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

# HTML Ŭ���� ���ε�
- �⺻������ v-bind:class �� �̿��Ͽ� ���ε� �Ѵ�.
- �Ϲ� class �Ӽ��� ������ �� �ִ�.
```
        <div class="static" 
             v-bind:class="{'active' : isActive, 'text-danger' : hasError}">
        Ŭ���� ���ε�
        </div>

            data: {
                isActive: true,
                hasError: false
            }

// ��� : <div class="static active">
```
- ������Ʈ�� �迭 ���·� Ű ���� ������ �� Vue���� ������ ���� Ŭ������ ������ ���� �ִ�.
```
<div v-bind:class="[activeClass, errorClass]"></div>

data: {
  activeClass: 'active',
  errorClass: 'text-danger'
}

// ��� : <div class="active text-danger"></div>
```
- style�� ���ε� �� �� �ִ�.
  - ������ ��� ����ǥ�� �Բ� ����ؾ� �Ѵٴ� ���� ������ �ʿ䰡 �ִ�.
```
<div v-bind:style="{ color: activeColor, fontSize: fontSize + 'px' }"></div>

data: {
  activeColor: 'red',
  fontSize: 30
}
```
- ���� ���� �迭�� �����ϴ� ��� (2.3 ���� �̻�)
```
<div v-bind:style="{ display: ['-webkit-box', '-ms-flexbox', 'flex'] }"></div>
```

# data�� �迭 ���� ����
- data�� �迭�� �߰��ϴ� ��� : push�� ����Ѵ�.
- data�� ���̸� �����ؾ� �ϴ� ��� : splice�� ����Ѵ�.
```
            data: {
                todos: [
                    {text : 'Javascript ����'},
                    {text : 'Vue ����'},
                    {text : '���� �����'}
                ]
            }

// �߰�
app8.todos.push({ text: 'New item' })
// �߰�(methods �ȿ���)
this.todos.splice(index, 0, value)

// length ����
app8.todos.splice(newLength)

// ����(methods �ȿ���)
this.todos.splice(index, 1)
```

- ������Ʈ�� ���� �����ϰų�, �߰��ϴ� ��� : Vue.set�� ����Ѵ�.
```
var vm = new Vue({
  data: {
    userProfile: {
      name: 'Anika'
    }
  }
})

// �����ϴ� ���
Vue.set(vm.userProfile, name, 'InHaeng')

// �߰��ϴ� ���
Vue.set(vm.userProfile, 'age', 27)

// �������� �������� �ʴ� �߰� (�������� ����)
vm.userProfile2 = 'hihi'
```

- ���͸��� ����Ͽ� �迭�� ��� ���� ��� : filter�� ����Ѵ�.
  - methods �Ӽ��� computed �Ӽ��� �ޱ򸮹Ƿ� �����ؼ� ����� �ʿ䰡 �ִ�.
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

# �̺�Ʈ �ڵ鸵
- https://kr.vuejs.org/v2/guide/events.html
- ���� �̺�Ʈ��
- v-on:click.prevent.self : ��� Ŭ�� ����
- v-on:click.self.prevent : ������Ʈ ��ü�� ���� Ŭ���� �����մϴ�.
```
<!-- Ŭ�� �̺�Ʈ ���İ� �ߴܵ˴ϴ� -->
<a v-on:click.stop="doThis"></a>

<!-- ���� �̺�Ʈ�� �������� �ٽ� �ε� ���� �ʽ��ϴ� -->
<form v-on:submit.prevent="onSubmit"></form>

<!-- ���ľ�� ü�̴� �����մϴ� -->
<a v-on:click.stop.prevent="doThat"></a>

<!-- �ܼ��� ���ľ ����� �� �ֽ��ϴ� -->
<form v-on:submit.prevent></form>

<!-- �̺�Ʈ �����ʸ� �߰��� �� ĸó��带 ����մϴ� -->
<!-- ��, ���� ������Ʈ�� ������� �ϴ� �̺�Ʈ�� �ش� ������Ʈ���� ó���Ǳ� ���� ���⼭ ó���մϴ�. -->
<div v-on:click.capture="doThis">...</div>

<!-- event.target�� ������Ʈ ��ü�� ��쿡�� Ʈ���Ÿ� ó���մϴ� -->
<!-- �ڽ� ������Ʈ������ �ȵ˴ϴ� -->
<div v-on:click.self="doThat">...</div>

<!-- Ŭ�� �̺�Ʈ�� �ִ� �ѹ��� Ʈ���� �˴ϴ�. -->
<a v-on:click.once="doThis"></a>

<!-- ��ũ���� �⺻ �̺�Ʈ�� ����� �� �����ϴ�. -->
<div v-on:scroll.passive="onScroll">...</div>
```
- ���콺, Ű���� Ű ���� �̺�Ʈ��
```
<!-- keyCode�� 13�� ���� `vm.submit()`�� ȣ���մϴ�  -->
<input v-on:keyup.13="submit">

<!-- Alt(Ctrl, Shift) + C -->
<input v-on:keyup.alt.67="clear">

<!-- Ctrl(Alt, Shift) + Click -->
<div v-on:click.ctrl="doSomething">Do something</div>

<!-- Ctrl Ű�� �������� ���� ����˴ϴ�. -->
<button v-on:click.ctrl.exact="onCtrlClick">A</button>

<!-- �Ʒ� �ڵ�� �ý��� Ű�� ������ ���� ������ ��쿡�� �۵��մϴ�. -->
<button v-on:click.exact="onClick">A</button>

click.left
click.right
click.middle
```
