const char * WEB_PAGE_MAIN = R"=====(<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SmartThing control page</title>
    <script type="module" crossorigin src="/assets/index.js"></script>
    <link rel="stylesheet" href="/assets/index.css">
  </head>
  <body>
    <h1 class="title">Control panel</h1>
    <div id="control-panel" class="bordered"></div>
    <div id="toasts-list" class="list"></div>
  </body>
</html>)=====";

const char * STYLE_PAGE_MAIN = R"=====(:root{--vt-c-white: #ffffff;--vt-c-white-soft: #f8f8f8;--vt-c-white-mute: #f2f2f2;--vt-c-black: #181818;--vt-c-black-soft: #222222;--vt-c-black-mute: #282828;--vt-c-indigo: #2c3e50;--vt-c-divider-light-1: rgba(60, 60, 60, .29);--vt-c-divider-light-2: rgba(60, 60, 60, .12);--vt-c-divider-dark-1: rgba(84, 84, 84, .65);--vt-c-divider-dark-2: rgba(84, 84, 84, .48);--vt-c-text-light-1: var(--vt-c-indigo);--vt-c-text-light-2: rgba(60, 60, 60, .66);--vt-c-text-dark-1: var(--vt-c-white);--vt-c-text-dark-2: rgba(235, 235, 235, .64);--color-positive: hsla(160, 100%, 37%, 1);--color-accent: #2c3e50;--color-danger: rgba(147, 4, 4, .453);--vt-c-svg-fill: #666666;--background-tilt: #141313cd;--doc-height: 50px;--border-radius: 10px;--section-gap: 160px;--default-gap: 5px;--toast-width: 300px;--toast-min-height: 50px;--icon-size: 35px}:root{--color-background: var(--vt-c-white);--color-background-soft: var(--vt-c-white-soft);--color-background-mute: var(--vt-c-white-mute);--color-border: var(--vt-c-divider-light-2);--color-border-hover: var(--vt-c-divider-light-1);--color-heading: var(--vt-c-text-light-1);--color-text: var(--vt-c-text-light-1);--color-svg-fill: var() }@media (prefers-color-scheme: dark){:root{--color-background: var(--vt-c-black);--color-background-soft: var(--vt-c-black-soft);--color-background-mute: var(--vt-c-black-mute);--color-border: var(--vt-c-divider-dark-2);--color-border-hover: var(--vt-c-divider-dark-1);--color-heading: var(--vt-c-text-dark-1);--color-text: var(--vt-c-text-dark-2)}}*,*:before,*:after{box-sizing:border-box;margin:0;font-weight:400}body{min-height:100vh;color:var(--color-text);background:var(--color-background);transition:color .5s,background-color .5s;line-height:1.6;font-family:Inter,-apple-system,BlinkMacSystemFont,Segoe UI,Roboto,Oxygen,Ubuntu,Cantarell,Fira Sans,Droid Sans,Helvetica Neue,sans-serif;font-size:15px;text-rendering:optimizeLegibility;-webkit-font-smoothing:antialiased;-moz-osx-font-smoothing:grayscale}#control-panel{display:flex;flex-direction:row;column-gap:var(--default-gap);margin:0 auto;width:1000px}#toasts-list{position:absolute;bottom:5px;right:5px;z-index:999}a,.green{text-decoration:none;color:var(--color-positive);transition:.4s}.red{text-decoration:none;color:var(--color-danger);transition:.4s}.title{text-align:center;text-decoration:none;color:var(--color-positive)}.btn{background-color:#00bd7e33;border-color:transparent;border-radius:var(--border-radius);min-width:90px;min-height:40px;color:#000}.btn:hover{opacity:.5;cursor:pointer}input,select{min-height:40px;font-size:18px;background-color:var(--color-background);color:var(--color-text);outline:none;border:1px solid var(--color-border);border-radius:var(--border-radius)}.bordered{border:solid;border-color:var(--color-border);border-radius:var(--border-radius);padding:5px}@media (hover: hover){a:hover{background-color:#00bd7e33;cursor:pointer}}.slide-left-enter-active{transition:all .5s ease}.slide-left-enter-from{transform:translate(-200px);opacity:0}.field-container{display:grid;grid-template-columns:1fr 1fr;border-radius:var(--border-radius)}input,select{background-color:var(--color-background);color:var(--color-text);outline:none;border:1px solid var(--color-border);border-radius:var(--border-radius)}.field-container .input-with-slot{display:flex;flex-direction:row;border:1px solid var(--color-border);border-radius:var(--border-radius)}.input-with-slot input{width:100%;border:none}.field-label{text-align:center}.list{display:flex;flex-direction:column;row-gap:var(--default-gap)}.required{background-color:#bd090033;color:#000}.loading-spinner{text-align:center}.menu-panel{display:flex;flex-direction:row;width:100%}.menu-items{width:250px}.menu-items h2{transition:.5s;cursor:pointer;border:solid;border-color:var(--color-border);border-radius:var(--border-radius);padding:5px;text-align:center}.menu-item-content{position:relative;width:calc(100% - 250px);margin-left:5px}.menu-selected{background-color:var(--vt-c-black-mute)}.update-button{position:absolute;top:0;right:0}.controls-holder{position:absolute;bottom:0;width:100%;display:flex;flex-direction:row;gap:var(--default-gap)}.controls-holder button{width:100%}.callback-title{flex:1 1 auto;text-align:start}.callback-header{display:flex;flex-direction:row;gap:var(--default-gap);position:relative}.callbacks-list-view{max-height:80vh;overflow-y:auto;margin-top:var(--default-gap)}.callback-view-controls{display:flex;flex-direction:row-reverse;column-gap:var(--default-gap);margin-bottom:5px}.toast{position:relative;border:1px solid var(--color-border);border-radius:var(--border-radius);width:var(--toast-width);min-height:var(--toast-min-height);padding:10px 5px 5px;z-index:1000;transition:.4s}.toast button{background-color:transparent;border-color:transparent;position:absolute;top:0;right:0;outline:none;-webkit-user-select:none;user-select:none}.toast h2,h3{text-align:center})=====";

const char * SCRIPT_PAGE_MAIN = R"=====(var N=Object.defineProperty;var F=(t,e,n)=>e in t?N(t,e,{enumerable:!0,configurable:!0,writable:!0,value:n}):t[e]=n;var H=(t,e,n)=>(F(t,typeof e!="symbol"?e+"":e,n),n);(function(){const e=document.createElement("link").relList;if(e&&e.supports&&e.supports("modulepreload"))return;for(const i of document.querySelectorAll('link[rel="modulepreload"]'))s(i);new MutationObserver(i=>{for(const a of i)if(a.type==="childList")for(const o of a.addedNodes)o.tagName==="LINK"&&o.rel==="modulepreload"&&s(o)}).observe(document,{childList:!0,subtree:!0});function n(i){const a={};return i.integrity&&(a.integrity=i.integrity),i.referrerPolicy&&(a.referrerPolicy=i.referrerPolicy),i.crossOrigin==="use-credentials"?a.credentials="include":i.crossOrigin==="anonymous"?a.credentials="omit":a.credentials="same-origin",a}function s(i){if(i.ep)return;i.ep=!0;const a=n(i);fetch(i.href,a)}})();let{host:E}=window.location;E==="localhost:5173"&&(E="192.168.2.2");const p={getSystemInfo:async()=>{try{const{data:t}=await u({path:"/info/system"});return t||{}}catch(t){console.error(t)}},getActions:async()=>{try{const{data:t}=await u({path:"/info/actions"});return t||{}}catch(t){console.error(t)}},getConfigInfo:async()=>{try{const{data:t}=await u({path:"/info/config"});return t||{}}catch(t){console.error(t)}},getWifiSettings:async()=>{try{const{data:t}=await u({path:"/wifi"});return t}catch(t){console.error(t)}},saveWifiSettings:async({ssid:t,password:e,mode:n})=>{try{const{status:s}=await u({path:"/wifi",method:"POST",payload:{ssid:t,password:e,mode:n}});return s===200}catch(s){console.error(s)}},saveName:async t=>{try{const{status:e}=await u({path:"/info/system",method:"PUT",payload:{name:t}});return e===200}catch(e){console.error(e)}},performAction:async t=>{try{const{status:e}=await u({method:"PUT",path:"/actions",params:{action:t}});return e===200}catch(e){console.error(e)}},getSensors:async()=>{try{const{data:t}=await u({path:"/sensors"});return t||{}}catch(t){console.error(t)}},getStates:async()=>{try{const{data:t}=await u({path:"/states"});return t||{}}catch(t){console.error(t)}},getConfigValues:async()=>{try{const{data:t}=await u({path:"/config"});return t||{}}catch(t){console.error(t)}},deleteAllConfigValues:async()=>{try{const{status:t}=await u({method:"DELETE",path:"/config/delete/all"});return t===200}catch(t){console.error(t)}},saveConfigValues:async t=>{try{const{status:e}=await u({method:"POST",path:"/config",payload:t});return e===200}catch(e){console.error(e)}},getCallbacks:async({observable:{name:t,type:e}})=>{try{const{data:n}=await u({path:"/callback/by/observable",params:{name:t,type:e}});return n||[]}catch(n){console.error(n)}},getCallbacksTemplates:async()=>{try{const{data:t}=await u({path:"/callback/template"});return t||[]}catch(t){console.error(t)}},createCallback:async({observable:{name:t,type:e},callback:n})=>{try{const{status:s}=await u({path:"/callback",method:"POST",payload:{observable:{name:t,type:e},callback:n}});return s===201}catch(s){console.error(s)}},updateCallback:async({observable:{name:t,type:e},callback:n})=>{try{const{status:s}=await u({path:"/callback",method:"PUT",payload:{observable:{name:t,type:e},callback:n}});return s===200}catch(s){console.error(s)}},deleteCallback:async({observable:{name:t,type:e},id:n})=>{try{const{status:s}=await u({path:"/callback",method:"DELETE",params:{name:t,type:e,id:n}});return s===200}catch(s){console.error(s)}},getMetrics:async()=>{try{const{data:t}=await u({path:"/metrics"});return t||{}}catch(t){console.error(t)}}};function D(t){if(!t||!Object.keys(t))return"";const e=Object.entries(t).map(([n,s])=>`${n}=${s}`);return e.length>0?"?"+e.join("&"):""}function u({method:t="GET",path:e,payload:n,params:s}){let i=new XMLHttpRequest;i.open(t,`http://${E}${e[0]!="/"?"/":""}${e}${D(s)}`),i.setRequestHeader("Accept","application/json"),n&&i.setRequestHeader("Content-Type","application/json");let a;const o=new Promise(c=>a=c);return i.onreadystatechange=()=>{i.readyState===4&&a({data:i.response?JSON.parse(i.response):null,status:i.status})},i.send(n?JSON.stringify(n):null),o}const r={container:({bordered:t=!1})=>{const e=document.createElement("div");return t&&e.classList.add("bordered"),e},list:()=>{const t=document.createElement("div");return t.classList.add("list"),t},button:({id:t,label:e,labelElement:n="h3",onClick:s,danger:i=!1,visible:a=!0})=>{const o=document.createElement("button");t&&(o.id=t),o.classList.add("btn");const c=`<${n}>${e}</${n}>`;return o.innerHTML=c,s&&(o.onclick=async()=>{o.disabled=!0,o.innerHTML="Loading...";try{await s()}catch(d){console.error(d)}finally{o.innerHTML=c,o.disabled=!1}}),i&&(o.style.backgroundColor="var(--color-danger)"),a||(o.style.display="None"),o},icon:({id:t,icon:e,onClick:n=()=>{},visible:s=!0})=>{const i=document.createElement("span");return t&&(i.id=t),i.ariaHidden=!0,i.role="img",i.innerHTML=e,s||(i.style.display="None"),i.style.cursor="pointer",i.onclick=n,i},input:({id:t,label:e,value:n,disabled:s=!1,type:i="text",slot:a,props:o={}})=>{const c=document.createElement("div");c.classList.add("field-container");const d=document.createElement("h2");d.classList.add("field-label"),d.innerHTML=e;const m=document.createElement("div");m.classList.add("input-with-slot");const h=document.createElement("input");return t&&(h.id=t),h.disabled=s,h.value=n,h.type=i,Object.entries(o).forEach(([g,w])=>h.setAttribute(g,w)),m.appendChild(h),a&&m.appendChild(a),c.append(d,m),c},combobox:({id:t,value:e,values:n,label:s,disabled:i=!1,onChange:a,props:o={}})=>{const c=document.createElement("div");if(c.classList.add("field-container"),s){const m=document.createElement("h2");m.classList.add("field-label"),m.innerHTML=s,c.appendChild(m)}const d=document.createElement("select");return t&&(d.id=t),d.disabled=i,d.appendChild(document.createElement("option")),a&&(d.onchange=()=>a(d.value)),Object.entries(o).forEach(([m,h])=>d.setAttribute(m,h)),c.append(d),M(c,n),e&&(d.value=e),c},tree:t=>{const e=document.createElement("ul");return Object.entries(t).forEach(([n,s])=>e.appendChild(O({key:n,value:s}))),e},controlsHolder:()=>{const t=document.createElement("div");return t.classList.add("controls-holder"),t}},v={pencil:'<svg fill="currentColor" class="material-design-icon__svg" width="35" height="35" viewBox="0 0 24 24"><path d="M20.71,7.04C21.1,6.65 21.1,6 20.71,5.63L18.37,3.29C18,2.9 17.35,2.9 16.96,3.29L15.12,5.12L18.87,8.87M3,17.25V21H6.75L17.81,9.93L14.06,6.18L3,17.25Z"><!----></path></svg>',trash:'<svg fill="currentColor" class="material-design-icon__svg" width="35" height="35" viewBox="0 0 24 24"><path d="M19,4H15.5L14.5,3H9.5L8.5,4H5V6H19M6,19A2,2 0 0,0 8,21H16A2,2 0 0,0 18,19V7H6V19Z"><!----></path></svg>',cross:'<svg fill="currentColor" class="material-design-icon__svg" width="35" height="35" viewBox="0 0 24 24"><path d="M13.46,12L19,17.54V19H17.54L12,13.46L6.46,19H5V17.54L10.54,12L5,6.46V5H6.46L12,10.54L17.54,5H19V6.46L13.46,12Z"><!----></path></svg>',save:'<svg fill="currentColor" class="material-design-icon__svg" width="35" height="35" viewBox="0 0 24 24"><path d="M15,9H5V5H15M12,19A3,3 0 0,1 9,16A3,3 0 0,1 12,13A3,3 0 0,1 15,16A3,3 0 0,1 12,19M17,3H5C3.89,3 3,3.9 3,5V19A2,2 0 0,0 5,21H19A2,2 0 0,0 21,19V7L17,3Z"><!----></path></svg>',update:'<svg fill="currentColor" class="material-design-icon__svg" width="35" height="35" viewBox="0 0 24 24"><path d="M17.65,6.35C16.2,4.9 14.21,4 12,4A8,8 0 0,0 4,12A8,8 0 0,0 12,20C15.73,20 18.84,17.45 19.73,14H17.65C16.83,16.33 14.61,18 12,18A6,6 0 0,1 6,12A6,6 0 0,1 12,6C13.66,6 15.14,6.69 16.22,7.78L13,11H20V4L17.65,6.35Z"></path></svg>'};function M(t,e){if(!e)return;const n=t.getElementsByTagName("select")[0];if(!n){console.error("Can't find select in combobox");return}let s;Array.isArray(e)?s=e.map(i=>({key:i,caption:i})):s=Object.entries(e).map(([i,a])=>({key:i,caption:a})),s.forEach(({key:i,caption:a})=>{const o=document.createElement("option");o.value=i,o.innerHTML=a,n.appendChild(o)})}const O=({key:t,value:e})=>{const n=document.createElement("li");return n.append(t+": ",$(e)),n},$=t=>{if(Array.isArray(t)){const e=document.createElement("ul");return t.forEach(n=>{const s=document.createElement("li");s.innerHTML=n,e.appendChild(s)}),e}else if(t instanceof Object){const e=document.createElement("ul");return Object.entries(t).forEach(([n,s])=>{const i=document.createElement("li");i.appendChild(O({key:n,value:s})),e.appendChild(i)}),e}else{const e=document.createElement("span");return e.innerHTML=t,e}};let B=0;const j=5e3,b={INFO:"info",SUCCESS:"success",WARNING:"warning",ERROR:"error"};function A(t){const e=document.getElementById(t);e&&e.remove()}function V(t){switch(t){case b.ERROR:return"rgb(171, 12, 12)";case b.SUCCESS:return"rgb(2, 147, 74)";case b.WARNING:return"rgb(147, 106, 2)";default:return"rgb(0, 112, 122)"}}function y({type:t=b.INFO,caption:e,description:n=""}){const s=document.createElement("div");s.classList.add("toast");const i="toast-"+B++;s.id=i,s.style.backgroundColor=V(t);const a=document.createElement("h2");a.id=i+"-caption",a.innerHTML=e;const o=document.createElement("div");o.id=i+"-description",o.style.overflowWrap="break-word",o.innerHTML=n;const c=document.createElement("button");c.id=i+"-close",c.innerHTML="X",c.onclick=()=>A(i),s.append(a,o,c),document.getElementById("toasts-list").appendChild(s),setTimeout(()=>A(i),j)}const l={info:({caption:t,description:e})=>y({caption:t,description:e}),error:({caption:t,description:e})=>y({type:b.ERROR,caption:t,description:e}),success:({caption:t,description:e})=>y({type:b.SUCCESS,caption:t,description:e}),warning:({caption:t,description:e})=>y({type:b.WARNING,caption:t,description:e})};function L(t){return typeof t!="string"||t.length==0?"":t.split("").reduce((e,n)=>(n==="_"?e+=" ":n===n.toUpperCase()?e+=" "+n.toLowerCase():e+=n,e),"")}const x=["id","type","readonly"];function R(t){return x.includes(t)}class S{constructor({id:e="",callback:n,template:s,observable:i,parent:a}){this.id=e,this.callback=n,this.template=s,this.observable=i,this.parent=a,this.fields=Object.entries(this.callback).filter(([o,c])=>!R(o)).reverse(),this.controls={delete:r.icon({icon:v.trash,onClick:()=>this.delete()}),edit:r.icon({icon:v.pencil,onClick:()=>this.edit()}),cancel:r.icon({icon:v.cross,onClick:()=>this.cancel(),visible:!1}),save:r.icon({icon:v.save,onClick:()=>this.save(),visible:!1})}}create(){const e=document.getElementById(this.id);if(this.id&&e)return e;const n=r.container({bordered:!0});n.id=this.id;const s=document.createElement("div");s.classList.add("callback-header");const i=document.createElement("h3"),{id:a,caption:o,type:c}=this.callback;i.innerHTML=`[${a}] ${o||L(c)}`,i.classList.add("title","callback-title");const d=document.createElement("div");d.classList.add("callback-view-controls"),Object.values(this.controls).forEach(h=>d.appendChild(h)),s.append(i,d);const m=r.list();return this.fields.forEach(([h,g])=>{const{required:w}=this.template[h]||!1,T={id:`cb_${a}_${h}`,label:L(h),value:g,disabled:!0,props:{required:w}};let C;this.template[h]&&this.template[h].values?C=r.combobox({...T,values:this.template[h].values}):C=r.input(T),m.appendChild(C)}),n.append(s,m),n}edit(e=!0){this.fields.forEach(([n,s])=>{document.getElementById(`cb_${this.callback.id}_${n}`).disabled=!e}),e?(this.controls.cancel.style.display="",this.controls.save.style.display="",this.controls.delete.style.display="None",this.controls.edit.style.display="None"):(this.controls.cancel.style.display="None",this.controls.save.style.display="None",this.controls.delete.style.display="",this.controls.edit.style.display="")}validate(){let e=!0;return this.fields.forEach(([n,s])=>{const i=document.getElementById(`cb_${this.callback.id}_${n}`);i.getAttribute("required")=="true"&&!i.value&&(e=!1,i.classList.add("required"))}),e}async save(){if(!this.validate())return;this.fields.forEach(([n,s])=>{this.callback[n]=document.getElementById(`cb_${this.callback.id}_${n}`).value});let e;this.callback.id==="New"?e=await p.createCallback({observable:this.observable,callback:this.callback}):e=await p.updateCallback({observable:this.observable,callback:this.callback}),e?(l.success({caption:`Callback ${this.callback.id==="New"?"created":"updated"}!`}),document.getElementById(this.id).remove(),this.parent.update()):l.error({caption:"Failed to save toast",description:"Check device logs for additional information"})}async delete(){confirm("Are you sure you wan to delete callback "+this.callback.id+"?")&&(await p.deleteCallback({observable:this.observable,id:this.callback.id})?(l.success({caption:"Callback deleted"}),this.parent.update()):l.error({caption:"Failed to delete callback",description:"Check device logs for additional information"}))}cancel(){this.callback.id==="New"?(document.getElementById(this.id).remove(),this.parent.update()):this.edit(!1)}}class _{constructor({id:e="",observable:n}){this.id=e,this.observable=n}create(){const e=document.getElementById(this.id);if(this.id&&e)return e;const n=document.createElement("div");return n.id=this.id,this.comboboxTemplates=r.combobox({values:[],label:"Add callback of type",onChange:s=>{this.addNewCallback(s)}}),this.list=r.list(),this.list.id="cb_list_"+this.id,this.list.classList.add("callbacks-list-view"),n.append(this.comboboxTemplates,this.list),this.firstLoad(),n}update(){this.loadCallbacks()}async firstLoad(){await this.loadTemplates(),this.loadCallbacks()}async loadTemplates(){if(this.templates=await p.getCallbacksTemplates(),!this.templates){l.error({caption:"Something gone wrong",description:"Failed to fetch callbacks templates"});return}M(this.comboboxTemplates,Object.keys(this.templates).filter(e=>e!=="default").reduce((e,n)=>(e[n]=L(n),e),{}))}async loadCallbacks(){if(this.templates){if(this.list.innerHTML="",this.callbacks=void 0,this.callbacks=await p.getCallbacks({observable:this.observable}),!this.callbacks){l.error({caption:"Something gone wrong",description:`Failed to fetch callbacks for [${this.observable.type}]${this.observable.name}`});return}if(!this.callbacks||this.callbacks.length===0){this.list.innerHTML="<h3 class='title'>No callbacks added yet</h3>";return}this.callbacks.forEach(e=>this.list.appendChild(new S({id:"cb_"+e.id,callback:e,template:this.templates[e.type],observable:this.observable,parent:this}).create()))}}addNewCallback(e){const n=document.getElementById("cb_new");if(n&&n.remove(),!e)return;const s={...this.templates[e],...this.templates.default},i=Object.entries(s).reduce((o,[c,d])=>(o[c]=d.default||"",o),{id:"New",type:e}),a=new S({id:"cb_new",callback:i,template:s,observable:this.observable,parent:this});this.list.prepend(a.create()),a.edit()}}const f="Something gone wrong";class k{constructor(e,n){H(this,"selected",{});this.id=e,this.menuItems=n}create(){const e=document.createElement("div");e.classList.add("menu-panel"),this.viewDiv=document.createElement("div"),this.viewDiv.classList.add("menu-items","list"),this.viewDiv.id=this.id,Object.entries(this.menuItems).forEach(([s,{name:i}])=>{const a=document.createElement("h2");a.id=s,a.innerHTML=i,a.onclick=()=>this.open(s),this.viewDiv.appendChild(a)}),this.contentDiv=document.createElement("div"),this.contentDiv.classList.add("menu-item-content"),this.contentDiv.id=this.id+"-content",this.loadingTitle=document.createElement("h2"),this.loadingTitle.classList.add("title"),this.loadingTitle.style.display="None",this.loadingTitle.innerHTML="Loading...",this.contentDiv.appendChild(this.loadingTitle);const n=r.icon({id:this.id+"-update",icon:v.update,onClick:()=>this.updateContent()});return n.classList.add("update-button"),this.contentDiv.appendChild(n),e.append(this.viewDiv,this.contentDiv),e}open(e){const n=document.getElementById(e);if(!n){console.error("Failed to open menuItem id="+e+": element not found");return}this.selected.item&&(this.selected.item.classList.remove("menu-selected"),this.selected.content.style.display="None");let s=document.getElementById(e+"-content");s?s.style.display="":(s=this.createContent(e,!0),this.contentDiv.appendChild(s)),n.classList.add("menu-selected"),this.selected.name=e,this.selected.item=n,this.selected.content=s}updateContent(){this.selected&&(this.selected.content.remove(),this.selected.content=this.createContent(this.selected.name,!0),this.contentDiv.appendChild(this.selected.content))}createContent(e,n=!1){const s=e+"-content",i=document.createElement("div");if(i.id=s,n||(i.style.display="None"),this.menuItems[e].title){const a=document.createElement("h1");a.classList.add("title"),a.innerHTML=this.menuItems[e].title,i.appendChild(a)}return this.loadContent(i,e),i}async loadContent(e,n){try{this.loading(!0),e.appendChild(await this.menuItems[n].content())}catch(s){console.error(s)}finally{this.loading(!1)}}loading(e){this.loadingTitle.style.display=e?"":"None"}}const W={info:{name:"Information",title:"Device information",content:async()=>{const t=await p.getSystemInfo();if(!t){l.error({caption:f,description:"Failed to fetch system information"});return}const e=r.list();return e.append(r.input({id:"device-name",label:"Device name",value:t.name||"",slot:r.button({id:"save-device-name",label:"save",onClick:async()=>{const n=document.getElementById("device-name"),s=n.value;if(!s||s.length===0){n.classList.add("required"),l.error({caption:"Device name can't be empty!"});return}const i=await p.saveName(s);n.classList.remove("required"),i?l.success({caption:"Name updated",description:"New device name: "+s}):l.error({caption:"Name update failed",description:"Failed to update device name"})}})}),r.input({label:"Device type",value:t.type,disabled:!0}),r.input({label:"Firmware version",value:t.version,disabled:!0,type:"number"}),r.input({label:"Chip model",value:t.chip_model,disabled:!0}),r.input({label:"Chip revision",value:t.chip_revision,disabled:!0})),e}},wifi:{name:"WiFi",title:"WiFi settings",content:async()=>{const{settings:t,modes:e}=await p.getWifiSettings();if(!t){l.error({caption:f,description:"Failed to fetch WiFi settings"});return}const n=r.list();n.append(r.input({id:"ssid",label:"SSID",value:t.ss||""}),r.input({id:"password",label:"password",value:t.ps||""}),r.combobox({id:"mode",label:"mode",values:e,value:t.md}));const s=r.controlsHolder();s.appendChild(r.button({label:"Save and reconnect",onClick:async()=>{await p.saveWifiSettings({ssid:document.getElementById("ssid").value||"",password:document.getElementById("password").value||"",mode:document.getElementById("mode").value||""})?l.success({caption:"WiFi settings updated"}):l.error({caption:"Failed to update WiFi settings",description:"Check device logs for additional information"})}}));const i=document.createElement("div");return i.append(n,s),i}},actions:{name:"Actions",title:"Actions list",content:async()=>{const t=await p.getActions();if(!t){l.error({caption:f,description:"Failed to fetch device actions"});return}const e=r.list();return Object.entries(t).forEach(([n,s])=>{e.appendChild(r.button({id:"action_"+n,label:s,labelElement:"h1",onClick:async()=>{await p.performAction(n)?l.success({caption:"Done",description:`Action "${s}" performed successfully`}):l.error({caption:"Action failed",description:`Failed to perform action "${s}"`})}}))}),e}},sensors:{name:"Sensors",title:"Sensors values",content:async()=>{const t=await p.getSensors();if(!t){l.error({caption:f,description:"Failed to fetch sensors"});return}const e=Object.entries(t).reduce((s,[i,{value:a,type:o}])=>(s["sensors-menu-"+i]={name:`${i} (${o}): ${a}`,title:"Callbacks",content:async()=>new _({id:"cb_view_"+i,observable:{type:"sensor",name:i}}).create()},s),{});return new k("sensors-menu",e).create()}},states:{name:"States",title:"Device states values",content:async()=>{const t=await p.getStates();if(!t){l.error({caption:f,description:"Failed to fetch device states"});return}const e=Object.entries(t).reduce((s,[i,a])=>(s["state-menu-"+i]={name:`${i}: ${a}`,title:"Callbacks",content:async()=>new _({id:"cb_view_"+i,observable:{type:"state",name:i}}).create()},s),{});return new k("states-menu",e).create()}},configuration:{name:"Configuration",title:"Configuration values",content:async()=>{const t=await p.getConfigInfo();if(!t){l.error({caption:f,description:"Failed to fetch configuration information"});return}const e=await p.getConfigValues();if(!e){l.error({caption:f,description:"Failed to fetch configuration values"});return}const n=r.list();Object.entries(t).forEach(([a,{caption:o,type:c}])=>{n.appendChild(r.input({id:a,label:o,type:c,value:e[a]||""}))});const s=r.controlsHolder();s.append(r.button({id:"config-delete",label:"Delete all values",danger:!0,labelElement:"h2",onClick:async()=>{confirm("Are you sure you want to delete all configuration values?")&&(await p.deleteAllConfigValues()?l.success({caption:"All values removed"}):l.error({caption:"Failed to delete configuration values"}))}}),r.button({id:"config-save",label:"Save",labelElement:"h2",onClick:async()=>{const a={};Object.keys(t).forEach(c=>a[c]=document.getElementById(c).value),await p.saveConfigValues(a)?l.success({caption:"Configuration updated"}):l.error({caption:"Failed to save configuration values"})}}));const i=document.createElement("div");return i.append(n,s),i}},metrics:{name:"Metrics",title:"Device metrics",content:async()=>{const t=await p.getMetrics();if(!t){l.error({caption:f,description:"Failed to fetch device metrics"});return}return r.tree(t)}}},I=new k("menu-main",W);window.onload=()=>{document.getElementById("control-panel").appendChild(I.create()),I.open("info")};)=====";