#include "Features.h"
#if ENABLE_WEB_PAGE 
const char* WEB_PAGE_MAIN PROGMEM = R"=====(<!DOCTYPE html>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <title>SmartThingDevice</title>
    <script type="module" crossorigin src="/assets/index.js"></script>
    <link rel="stylesheet" href="/assets/index.css">
  </head>
  <body>
    <h1 class="header">SmartThing device control panel</h1>
    <div id="control-panel" class="bordered"></div>
    <div id="toasts-list" class="list"></div>
  </body>
</html>
)=====";

const char* STYLE_PAGE_MAIN PROGMEM =
    R"=====(:root{--cp: hsla(160, 100%, 37%, 1);--cd: rgba(147, 4, 4, .453);--dg: 2px;--miw: 250px;--cb: #181818;--cb-m: #282828;--cb-s: #484848;--cbo: rgba(84, 84, 84, .48);--rbo: 10px;--ct: rgba(235, 235, 235, .64)}*,*:before,*:after{box-sizing:border-box;margin:0;font-weight:400}body{min-height:100vh;color:var(--ct);background:var(--cb);transition:color .5s,background-color .5s;line-height:1.6;font-family:Inter,-apple-system,BlinkMacSystemFont,Segoe UI,Roboto,Oxygen,Ubuntu,Cantarell,Fira Sans,Droid Sans,Helvetica Neue,sans-serif;font-size:15px;text-rendering:optimizeLegibility;-webkit-font-smoothing:antialiased;-moz-osx-font-smoothing:grayscale}#control-panel{display:flex;flex-direction:row;column-gap:var(--dg);margin:0 auto;width:1000px}#toasts-list{position:absolute;bottom:5px;right:5px;z-index:999}.header{text-align:center;text-decoration:none;color:#00bd7e}.btn{background-color:#00bd7e33;border-color:transparent;border-radius:var(--rbo);min-width:90px;min-height:40px;color:#000}.btn:hover{opacity:.5;cursor:pointer}input,select{min-height:40px;font-size:18px;background-color:var(--cb);color:var(--ct);outline:none;border:1px solid var(--cbo);border-radius:var(--rbo)}.bordered{border:solid 2px var(--cbo);border-radius:var(--rbo)}.container{display:flex;flex-direction:column;gap:var(--dg);height:100%}.field-container{display:grid;grid-template-columns:1fr 1fr;border-radius:var(--rbo)}.field-container{text-align:center}.field-container .input-with-slot{display:flex;flex-direction:row;border:1px solid var(--cbo);border-radius:var(--rbo)}.input-with-slot input{width:100%;border:none}.list{display:flex;flex-direction:column;row-gap:var(--dg)}.required{background-color:#bd090033;color:#000}.menu-panel{display:flex;flex-direction:row;flex:1 0 auto}.menu-items{width:var(--miw);padding:2px}.menu-items h2{transition:.5s;cursor:pointer;border-radius:var(--rbo);padding:5px;text-align:center;word-wrap:break-word}.menu-items h2:hover{transition:background-color .5s;background-color:var(--cb-m)}.menu-item-content{position:relative;width:calc(100% - var(--miw))}.menu-selected{background-color:var(--cb-s)}.controls-holder{margin-top:auto;display:flex;flex-direction:row;gap:var(--dg)}.controls-holder button{width:100%}.hook-header{flex:1 1 auto;text-align:start}.hook-header{display:flex;flex-direction:row;gap:var(--dg);position:relative}.hooks-list-view{max-height:80vh;overflow-y:auto;margin-top:var(--dg)}.hooks-list-view .container{border-top:1px solid var(--cbo)}.hook-view-controls{display:flex;flex-direction:row-reverse;column-gap:var(--dg);align-items:center}.toast{position:relative;border:1px solid var(--cbo);border-radius:var(--rbo);width:300px;min-height:50px;padding:10px 5px 5px;z-index:1000;transition:.4s}.toast h2,h3{text-align:center}.br{border-right:2px solid var(--cbo)})=====";

const char* SCRIPT_PAGE_MAIN PROGMEM = R"=====(var e=Object.defineProperty,t=(t,i,n)=>(((t,i,n)=>{i in t?e(t,i,{enumerable:!0,configurable:!0,writable:!0,value:n}):t[i]=n})(t,"symbol"!=typeof i?i+"":i,n),n);!function(){const e=document.createElement("link").relList;if(!(e&&e.supports&&e.supports("modulepreload"))){for(const e of document.querySelectorAll('link[rel="modulepreload"]'))t(e);new MutationObserver((e=>{for(const i of e)if("childList"===i.type)for(const e of i.addedNodes)"LINK"===e.tagName&&"modulepreload"===e.rel&&t(e)})).observe(document,{childList:!0,subtree:!0})}function t(e){if(e.ep)return;e.ep=!0;const t=function(e){const t={};return e.integrity&&(t.integrity=e.integrity),e.referrerPolicy&&(t.referrerPolicy=e.referrerPolicy),"use-credentials"===e.crossOrigin?t.credentials="include":"anonymous"===e.crossOrigin?t.credentials="omit":t.credentials="same-origin",t}(e);fetch(e.href,t)}}();const i=(e,t="h1")=>{const i=document.createElement(t);return i.classList.add("header"),i.innerHTML=e,i},n=(e={bordered:!1})=>{const t=document.createElement("div");return t.classList.add("container"),e.bordered&&t.classList.add("bordered"),t},a=()=>{const e=document.createElement("div");return e.classList.add("list"),e},o=({id:e,label:t,title:i,labelElement:n="h2",onClick:a,danger:o=!1,visible:s=!0})=>{const c=document.createElement("button");e&&(c.id=e),c.classList.add("btn");const d=`<${n}>${t}</${n}>`;return c.innerHTML=d,i&&(c.title=i),a&&(c.onclick=async()=>{c.disabled=!0,c.innerHTML="Loading...";try{await a()}catch(e){console.error(e)}finally{c.innerHTML=d,c.disabled=!1}}),o&&(c.style.backgroundColor="var(--cd)"),s||(c.style.display="none"),c},s=({id:e,icon:t,title:i,onClick:n=()=>{},visible:a=!0})=>{const o=document.createElement("span");return e&&(o.id=e),o.ariaHidden=!0,o.role="img",o.innerHTML=t,a||(o.style.display="none"),i&&(o.title=i),o.style.cursor="pointer",o.onclick=n,o},c=({id:e,label:t,value:i,title:n,disabled:a=!1,type:o="text",slot:s,props:c={}})=>{const d=document.createElement("div");d.classList.add("field-container");const l=document.createElement("h2");l.innerHTML=t,n&&(l.title=n);const r=document.createElement("div");r.classList.add("input-with-slot");const h=document.createElement("input");return e&&(h.id=e),h.disabled=a,h.value=i,h.type=o,Object.entries(c).forEach((([e,t])=>h.setAttribute(e,t))),r.appendChild(h),s&&r.appendChild(s),d.append(l,r),d},d=({id:e,value:t,values:i,label:n,disabled:a=!1,onChange:o,props:s={}})=>{const c=document.createElement("div");if(c.classList.add("field-container"),n){const e=document.createElement("h2");e.innerHTML=n,c.appendChild(e)}const d=document.createElement("select");return e&&(d.id=e),d.disabled=a,d.appendChild(document.createElement("option")),o&&(d.onchange=()=>o(d.value)),Object.entries(s).forEach((([e,t])=>d.setAttribute(e,t))),c.append(d),y(c,i),t&&(d.value=t),c},l=e=>{const t=document.createElement("ul");return Object.entries(e).forEach((([e,i])=>t.appendChild(b({key:e,value:i})))),t},r=()=>{const e=document.createElement("div");return e.classList.add("controls-holder"),e},h='<svg fill="currentColor" width="24" height="24" viewBox="0 0 24 24"><path d="M20.71,7.04C21.1,6.65 21.1,6 20.71,5.63L18.37,3.29C18,2.9 17.35,2.9 16.96,3.29L15.12,5.12L18.87,8.87M3,17.25V21H6.75L17.81,9.93L14.06,6.18L3,17.25Z"></path></svg>',p='<svg fill="currentColor" width="24" height="24" viewBox="0 0 24 24"><path d="M19,4H15.5L14.5,3H9.5L8.5,4H5V6H19M6,19A2,2 0 0,0 8,21H16A2,2 0 0,0 18,19V7H6V19Z"></path></svg>',u='<svg fill="currentColor" width="24" height="24" viewBox="0 0 24 24"><path d="M13.46,12L19,17.54V19H17.54L12,13.46L6.46,19H5V17.54L10.54,12L5,6.46V5H6.46L12,10.54L17.54,5H19V6.46L13.46,12Z"></path></svg>',m='<svg fill="currentColor" width="24" height="24" viewBox="0 0 24 24"><path d="M15,9H5V5H15M12,19A3,3 0 0,1 9,16A3,3 0 0,1 12,13A3,3 0 0,1 15,16A3,3 0 0,1 12,19M17,3H5C3.89,3 3,3.9 3,5V19A2,2 0 0,0 5,21H19A2,2 0 0,0 21,19V7L17,3Z"></path></svg>',v='<svg fill="currentColor" width="24" height="24" viewBox="0 0 24 24"><path d="M7,2V4H8V18A4,4 0 0,0 12,22A4,4 0 0,0 16,18V4H17V2H7M11,16C10.4,16 10,15.6 10,15C10,14.4 10.4,14 11,14C11.6,14 12,14.4 12,15C12,15.6 11.6,16 11,16M13,12C12.4,12 12,11.6 12,11C12,10.4 12.4,10 13,10C13.6,10 14,10.4 14,11C14,11.6 13.6,12 13,12M14,7H10V4H14V7Z"></path></svg>';function y(e,t){if(!t)return;const i=e.getElementsByTagName("select")[0];if(!i)return void console.error("Can't find select in combobox");let n;n=Array.isArray(t)?t.map((e=>({key:e,caption:e}))):Object.entries(t).map((([e,t])=>({key:e,caption:t}))),n.forEach((({key:e,caption:t})=>{const n=document.createElement("option");n.value=e,n.innerHTML=t,i.appendChild(n)}))}const b=({key:e,value:t})=>{const i=document.createElement("li");return i.append(e+": ",f(t)),i},f=e=>{if(Array.isArray(e)){const t=document.createElement("ul");return e.forEach((e=>{const i=document.createElement("li");i.innerHTML=e,t.appendChild(i)})),t}if(e instanceof Object){const t=document.createElement("ul");return Object.entries(e).forEach((([e,i])=>{const n=document.createElement("li");n.appendChild(b({key:e,value:i})),t.appendChild(n)})),t}{const t=document.createElement("span");return t.innerHTML=e,t}};class w{constructor(e,i,n){t(this,"selected",{}),this.id=e,this.menuItems=i,this.placeholder=n}create(){const e=document.createElement("div");return e.classList.add("menu-panel"),this.viewDiv=document.createElement("div"),this.viewDiv.classList.add("menu-items","list","br"),this.viewDiv.id=this.id,Object.entries(this.menuItems).forEach((([e,{name:t,title:i}])=>{const n=document.createElement("h2");n.id=e,n.innerHTML=t,i&&(n.title=i),n.onclick=()=>this.open(e),this.viewDiv.appendChild(n)})),this.contentDiv=document.createElement("div"),this.contentDiv.classList.add("menu-item-content"),this.contentDiv.id=this.id+"-content",this.loadingTitle=i("Loading...","h2"),this.loadingTitle.style.display="none",this.contentDiv.appendChild(this.loadingTitle),e.append(this.viewDiv,this.contentDiv),e}open(e){var t;if((null==(t=this.selected)?void 0:t.name)===e)return void this.updateContent();const i=document.getElementById(e);if(!i)return void console.error("Failed to open menuItem id="+e+": element not found");this.selected.item&&(this.selected.item.classList.remove("menu-selected"),this.selected.content.style.display="none");let n=document.getElementById(e+"-content");n?n.style.display="":(n=this.createContent(e),this.contentDiv.appendChild(n)),i.classList.add("menu-selected"),this.selected.name=e,this.selected.item=i,this.selected.content=n}updateContent(){this.selected&&(this.selected.content.remove(),this.selected.content=this.createContent(this.selected.name),this.contentDiv.appendChild(this.selected.content))}createContent(e){const t=e+"-content",a=n();return a.id=t,this.menuItems[e].header&&a.appendChild(i(this.menuItems[e].header)),this.loadContent(a,e),a}async loadContent(e,t){try{this.loading(!0),e.appendChild(await this.menuItems[t].content()??n())}catch(i){console.error(i)}finally{this.loading(!1)}}loading(e){this.loadingTitle.style.display=e?"":"none"}}let{hostname:g}=window.location;"localhost"===g&&(g="192.168.182.249");const E="Something gone wrong",k=async()=>(await U({path:"/info/system"})).data,C=async()=>(await U({path:"/actions/info"})).data,L=async()=>(await U({path:"/config/info"})).data,T=async()=>(await U({path:"/wifi"})).data,H=async e=>{await U({path:"/wifi",method:"POST",payload:e})},O=async e=>{await U({path:"/info/system",method:"PUT",payload:{name:e}})},I=async e=>{await U({method:"PUT",path:"/actions",params:{action:e}})},S=async()=>(await U({path:"/sensors"})).data,A=async()=>(await U({path:"/sensors/types"})).data,$=async()=>(await U({path:"/states"})).data,M=async()=>(await U({path:"/config/values"})).data,N=async()=>{await U({method:"DELETE",path:"/config/delete/all"})},j=async e=>{await U({method:"POST",path:"/config/values",payload:e})},D=async({observable:{name:e,type:t}})=>(await U({path:"/hooks/by/observable",params:{name:e,type:t}})).data,F=async e=>(await U({path:"/hooks/templates",params:{type:e}})).data,B=async({observable:{name:e,type:t},hook:i})=>{await U({path:"/hooks",method:"POST",payload:{observable:{name:e,type:t},hook:i}})},V=async({observable:{name:e,type:t},hook:i})=>{await U({path:"/hooks",method:"PUT",payload:{observable:{name:e,type:t},hook:i}})},R=async({observable:{name:e,type:t},id:i})=>{await U({path:"/hooks",method:"DELETE",params:{name:e,type:t,id:i}})},_=async({observable:{name:e,type:t},id:i})=>{await U({path:"/hooks/test",method:"GET",params:{name:e,type:t,id:i}})},x=async()=>(await U({path:"/features"})).data,P=async()=>(await U({path:"/metrics"})).data,q=async()=>{await U({path:"/danger/restart",method:"POST"})},W=async()=>{await U({path:"/danger/wipe",method:"POST"})};function U({method:e="GET",path:t,payload:i,params:n}){let a,o=new XMLHttpRequest;o.open(e,`http://${g}${"/"!=t[0]?"/":""}${t}${function(e){if(!e||!Object.keys(e))return"";const t=Object.entries(e).map((([e,t])=>`${e}=${t}`));return t.length>0?"?"+t.join("&"):""}(n)}`,!0),o.setRequestHeader("Accept","application/json"),i&&o.setRequestHeader("Content-Type","application/json");const s=new Promise((e=>a=e));return o.onloadend=()=>{let e;try{e=o.response?JSON.parse(o.response):null}catch(t){console.log(t)}a({data:e,status:o.status})},o.send(i?JSON.stringify(i):null),s}let G=0;const Z={INFO:"info",SUCCESS:"success",WARNING:"warning",ERROR:"error"};function J(e){const t=document.getElementById(e);t&&t.remove()}function z({type:e=Z.INFO,caption:t,description:i=""}){const n=document.createElement("div");n.classList.add("toast");const a="toast-"+G++;n.id=a,n.style.backgroundColor=function(e){switch(e){case Z.ERROR:return"rgb(171, 12, 12)";case Z.SUCCESS:return"rgb(2, 147, 74)";case Z.WARNING:return"rgb(147, 106, 2)";default:return"rgb(0, 112, 122)"}}(e);const o=document.createElement("h2");o.id=a+"-caption",o.innerHTML=t;const s=document.createElement("div");s.id=a+"-description",s.style.overflowWrap="break-word",s.innerHTML=i,n.append(o,s),n.onclick=()=>J(a),document.getElementById("toasts-list").appendChild(n),setTimeout((()=>J(a)),5e3)}const K=({caption:e,description:t})=>z({type:Z.ERROR,caption:e,description:t}),X=({caption:e,description:t})=>z({type:Z.SUCCESS,caption:e,description:t}),Y={name:"Information",content:async()=>{const e=await k();if(!e)return void K({caption:E,description:"Failed to fetch system information"});document.title=`SmartThing ${e.name}(${e.type})`;const t=a();return t.append(c({id:"device-name",label:"Device name",value:e.name||"",slot:o({id:"save-device-name",label:"save",onClick:async()=>{const e=document.getElementById("device-name"),t=e.value;if(!t||0===t.length)return e.classList.add("required"),void K({caption:"Device name can't be empty!"});try{await O(t),X({caption:"Name updated",description:"New device name: "+t})}catch(i){K({caption:"Name update failed",description:"Failed to update device name"})}finally{e.classList.remove("required")}}})}),c({label:"Device type",value:e.type,disabled:!0}),c({label:"Ip",value:e.ip,disabled:!0}),c({label:"Board",value:e.board,disabled:!0}),c({label:"Firmware version",value:e.version,disabled:!0,type:"number"})),t.style.padding="2px",t}},Q={name:"WiFi",content:async()=>{const{settings:e,modes:t}=await T();if(!e)return void K({caption:E,description:"Failed to fetch WiFi settings"});const i=a();i.append(c({id:"ssid",label:"SSID",value:e.ss||""}),c({id:"password",label:"password",value:e.ps||""}),d({id:"mode",label:"mode",values:t,value:e.md}));const s=r();s.appendChild(o({label:"Save and reconnect",onClick:async()=>{try{await H({ssid:document.getElementById("ssid").value||"",password:document.getElementById("password").value||"",mode:document.getElementById("mode").value||""}),X({caption:"WiFi settings updated"})}catch(e){K({caption:"Failed to update WiFi settings",description:"Check device logs for additional information"})}}}));const l=n();return l.append(i,s),l.style.padding="2px",l}},ee={name:"Actions",content:async()=>{const e=await C();if(!e)return i("No actions configured");const t=a();return Object.entries(e).forEach((([e,i])=>{t.appendChild(o({id:"action_"+e,label:i,title:`System name: ${e}`,labelElement:"h1",onClick:async()=>{try{await I(e),X({caption:"Done",description:`Action "${i}" performed successfully`})}catch(t){K({caption:"Action failed",description:`Failed to perform action "${i}"`})}}}))})),t.style.padding="2px",t}};function te(e){return"string"!=typeof e||0==e.length?"":e.split("").reduce(((e,t)=>("_"===t?e+=" ":t===t.toUpperCase()?e+=" "+t.toLowerCase():e+=t,e)),"")}const ie=["id","type","readonly"];class ne{constructor({id:e="",hook:t,template:i,observable:n,parent:a}){this.id=e,this.hook=t,this.template=i,this.observable=n,this.parent=a,this.fields=Object.entries(this.hook).filter((([e,t])=>!function(e){return ie.includes(e)}(e))).reverse(),this.controls={test:s({icon:v,onClick:()=>this.test(),title:"Make a test hook call"}),delete:s({icon:p,onClick:()=>this.delete()}),edit:s({icon:h,onClick:()=>this.edit()}),cancel:s({icon:u,onClick:()=>this.cancel(),visible:!1}),save:s({icon:m,onClick:()=>this.save(),visible:!1})}}create(){const e=document.getElementById(this.id);if(this.id&&e)return e;const t=n();t.id=this.id;const o=document.createElement("div");o.classList.add("hook-header");const{id:s,caption:l,type:r}=this.hook,h=i(`[${s}] ${l||te(r)}`,"h2");h.classList.add("hook-header");const p=document.createElement("div");p.classList.add("hook-view-controls"),Object.values(this.controls).forEach((e=>p.appendChild(e))),o.append(h,p);const u=a();return this.fields.forEach((([e,t])=>{const{required:i}=this.template[e]||!1,n={id:`cb_${s}_${e}`,label:te(e),value:t,disabled:!0,props:{required:i}};let a;a=this.template[e]&&this.template[e].values?d({...n,values:this.template[e].values}):c(n),u.appendChild(a)})),t.append(o,u),t}edit(e=!0){this.fields.forEach((([t,i])=>{document.getElementById(`cb_${this.hook.id}_${t}`).disabled=!e})),e?(this.controlsVisibile(["cancel","save"],!0),this.controlsVisibile(["delete","edit","test"],!1)):(this.controlsVisibile(["cancel","save"],!1),this.controlsVisibile(["delete","edit","test"],!0))}controlsVisibile(e,t){e.forEach((e=>this.controls[e].style.display=t?"":"none"))}validate(){let e=!0;return this.fields.forEach((([t,i])=>{const n=document.getElementById(`cb_${this.hook.id}_${t}`);"true"!=n.getAttribute("required")||n.value||(e=!1,n.classList.add("required"))})),e}async save(){if(this.validate()){this.fields.forEach((([e,t])=>{this.hook[e]=document.getElementById(`cb_${this.hook.id}_${e}`).value}));try{"New"===this.hook.id?(delete this.hook.id,await B({observable:this.observable,hook:this.hook})):await V({observable:this.observable,hook:this.hook}),X({caption:`Hook ${"New"===this.hook.id?"created":"updated"}!`}),document.getElementById(this.id).remove(),this.parent.update()}catch(e){K({caption:"Failed to save toast",description:"Check device logs for additional information"})}}}async delete(){if(confirm("Are you sure you wan to delete hook "+this.hook.id+"?"))try{await R({observable:this.observable,id:this.hook.id}),X({caption:"Hook deleted"}),this.parent.update()}catch(e){K({caption:"Failed to delete hook",description:"Check device logs for additional information"})}}async test(){try{await _({observable:this.observable,id:this.hook.id}),X({caption:"Hook called successfully!"})}catch(e){console.error(e),K({caption:"Failed to call hook"})}}cancel(){"New"===this.hook.id?(document.getElementById(this.id).remove(),this.parent.update()):this.edit(!1)}}class ae{constructor({id:e="",observable:t}){this.id=e,this.observable=t}create(){const e=document.getElementById(this.id);if(this.id&&e)return e;const t=document.createElement("div");return t.id=this.id,t.style.padding="2px",this.comboboxTemplates=d({values:[],label:"Add hook of type",onChange:e=>{this.addNewHook(e)}}),this.list=a(),this.list.id="cb_list_"+this.id,this.list.classList.add("hooks-list-view"),t.append(this.comboboxTemplates,this.list),this.firstLoad(),t}update(){this.loadHooks()}async firstLoad(){await this.loadTemplates(),this.loadHooks()}async loadTemplates(){this.templates=await F(this.observable.type),this.templates&&y(this.comboboxTemplates,Object.keys(this.templates).filter((e=>"default"!==e)).reduce(((e,t)=>(e[t]=te(t),e)),{}))}async loadHooks(){this.list.innerHTML="",this.hooks=await D({observable:this.observable}),this.hooks&&0!==this.hooks.length?this.hooks.forEach((e=>this.list.appendChild(new ne({id:"cb_"+e.id,hook:e,template:{...this.templates[e.type],...this.templates.default},observable:this.observable,parent:this}).create()))):this.list.appendChild(i("No hooks added yet","h3"))}addNewHook(e){const t=document.getElementById("cb_new");if(t&&t.remove(),!e)return;const i={...this.templates[e],...this.templates.default},n=Object.entries(i).reduce(((e,[t,i])=>(e[t]=i.default||"",e)),{id:"New",type:e}),a=new ne({id:"cb_new",hook:n,template:i,observable:this.observable,parent:this});this.list.prepend(a.create()),a.edit()}}const oe={info:Y,wifi:Q,actions:ee,sensors:{name:"Sensors",content:async()=>{const e=await S();if(!e||0===Object.keys(e).length)return i("No sensors configured","h2");const t=await A()??{},n=Object.entries(e).reduce(((e,[n,a])=>(e["sensors-menu-"+n]={name:`${n}: ${a}`,title:`Sensor type: ${t[n]}`,content:async()=>{var e,t;return void 0===(null==(e=window.features)?void 0:e.hooks)||1==(null==(t=window.features)?void 0:t.hooks)?new ae({id:"cb_view_"+n,observable:{type:"sensor",name:n}}).create():i("Hooks feature disabled in this build","h2")}},e)),{});return new w("sensors-menu",n).create()}},states:{name:"Device states",content:async()=>{const e=await $();if(!e||0===Object.keys(e).length)return i("No states configured","h2");const t=Object.entries(e).reduce(((e,[t,n])=>(e["state-menu-"+t]={name:`${t}: ${n}`,content:async()=>{var e,n;return void 0===(null==(e=window.features)?void 0:e.hooks)||1==(null==(n=window.features)?void 0:n.hooks)?new ae({id:"cb_view_"+t,observable:{type:"state",name:t}}).create():i("Hooks feature disabled in this build","h2")}},e)),{});return new w("states-menu",t).create()}},configuration:{name:"Configuration",content:async()=>{const e=await L();if(!e)return void K({caption:E,description:"Failed to fetch configuration information"});if(0===Object.keys(e).length)return i("No config entries","h2");const t=await M();if(!t)return void K({caption:E,description:"Failed to fetch configuration values"});const s=a();Object.entries(e).forEach((([e,{caption:i,type:n}])=>{s.appendChild(c({id:e,label:`${i} [${e}]`,title:`System name: ${e}\nValue type: ${n}`,type:n,value:t[e]||""}))}));const d=r();d.append(o({id:"config-delete",label:"Delete all values",danger:!0,onClick:async()=>{if(confirm("Are you sure you want to delete all configuration values?"))try{await N(),X({caption:"All values removed"})}catch(e){K({caption:"Failed to delete configuration values"})}}}),o({id:"config-save",label:"Save",onClick:async()=>{const t={};Object.keys(e).forEach((e=>t[e]=document.getElementById(e).value));try{await j(t),X({caption:"Configuration updated"})}catch(i){K({caption:"Failed to save configuration values"})}}}));const l=n();return l.append(s,d),l.style.padding="2px",l}},metrics:{name:"Metrics",content:async()=>{try{return l(await P())}catch(e){console.log(e),K({caption:E,description:"Failed to fetch device metrics"})}}},danger:{name:"Danger zone",content:async()=>{const e=a();return e.appendChild(i("Please, be careful with this actions!")),e.append(o({id:"restart",label:"Restart device",labelElement:"h1",danger:!0,onClick:()=>{confirm("Are you sure you want to restart device right now?")&&(q(),X({caption:"Restarting",description:"Device is restarting, please wait"}))}}),o({id:"wipe",label:"Wipe device settings",labelElement:"h1",danger:!0,onClick:()=>{confirm("THIS ACTIONS WILL DELETE ALL SETTINGS FROM DEVICE!")&&confirm("THERE IS NOY TO RESTORE THEM AFTER THIS ACTION!")&&confirm("THIS IS LAST CONFIRMATION")&&(W(),X({caption:"Settings wiped",description:"Device is gonna restart now, please wait"}))}})),e.style.padding="2px",e}}};window.onload=async()=>{const e=await x().catch((e=>{console.log("Failed to load features",e),K({caption:"Failed to load device features"})}))??{},t=new w("menu-main",Object.entries(oe).reduce(((t,[i,n])=>(void 0!==e[i]&&!0!==e[i]||(t[i]=n),t)),{}));window.features=e,document.getElementById("control-panel").appendChild(t.create()),t.open("info")};)=====";
#endif