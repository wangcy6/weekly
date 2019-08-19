

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

function _possibleConstructorReturn(self, call) { if (!self) { throw new ReferenceError("this hasn't been initialised - super() hasn't been called"); } return call && (typeof call === "object" || typeof call === "function") ? call : self; }

function _inherits(subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) Object.setPrototypeOf ? Object.setPrototypeOf(subClass, superClass) : subClass.__proto__ = superClass; }

function _toConsumableArray(arr) { if (Array.isArray(arr)) { for (var i = 0, arr2 = Array(arr.length); i < arr.length; i++) { arr2[i] = arr[i]; } return arr2; } else { return Array.from(arr); } }

define(['require','react','react-dom','classnames','resolve!i18n','css!focus/FleChecklist/FleChecklist','text!focus/img/close.svg','text!focus/FleChecklist/check.svg'],function (require) {
  

  var React = require('react');
  var ReactDOM = require('react-dom');
  var classnames = require('classnames');
  var i18n = require('resolve!i18n');
  require('css!focus/FleChecklist/FleChecklist');
  var closeSvg = require('text!focus/img/close.svg');
  var checkSvg = require('text!focus/FleChecklist/check.svg');

  var TOTAL_STEPS = 4;

  /**
   * A meter with equal-sized blocks showing progress. If the meter is empty, then it
   * shows progress text like "0/4".
   */
  var Meter = function Meter(props) {
    var getMeterSteps = function getMeterSteps() {
      var colors = ['#4ac087', '#2eb396', '#1baba2', '#20c05c'];

      return [].concat(_toConsumableArray(Array(props.total).keys())).map(function (i) {
        // Fill in completed blocks, left to right.
        if (i < props.numFilled) {
          // This step has been completed - fill it.
          return colors[i % colors.length];
        } else {
          // Unfilled block - leave it "blank".
          return '#fff';
        }
      }).map(function (backgroundColor, index) {
        return React.createElement('div', { key: index, style: { backgroundColor: backgroundColor }, className: 'FleChecklist-step' });
      });
    };

    var content = void 0;
    if (props.numFilled) {
      content = getMeterSteps();
    } else {
      var ratioString = '0/' + props.total;
      content = React.createElement(
        'div',
        { className: 'FleChecklist-ratio-text' },
        ratioString
      );
    }

    return React.createElement(
      'div',
      { className: 'FleChecklist-meter' },
      content
    );
  };

  Meter.propTypes = {
    numFilled: React.PropTypes.number.isRequired,
    total: React.PropTypes.number.isRequired
  };

  /**
   * An item in the checklist. Each item has a click handler and a "strikethrough" state.
   */
  var ChecklistItem = function ChecklistItem(props) {
    var headingClasses = classnames({
      'FleChecklist-complete': props.complete
    });

    var getChecklistIcon = function getChecklistIcon() {
      if (props.complete) {
        return React.createElement('div', {
          className: 'FleChecklist-complete',
          dangerouslySetInnerHTML: { __html: checkSvg }
        });
      } else {
        return React.createElement(
          'div',
          { className: 'FleChecklist-number' },
          props.stepNumber
        );
      }
    };

    return React.createElement(
      'div',
      { className: 'FleChecklist-checklist-item' },
      React.createElement(
        'div',
        { className: 'FleChecklist-checklist-icon' },
        getChecklistIcon()
      ),
      React.createElement(
        'h2',
        { className: headingClasses, onClick: props.onClick },
        React.createElement(
          'span',
          null,
          props.header
        )
      ),
      React.createElement(
        'p',
        null,
        props.description
      )
    );
  };

  ChecklistItem.propTypes = {
    complete: React.PropTypes.bool.isRequired,
    description: React.PropTypes.string.isRequired,
    header: React.PropTypes.string.isRequired,
    onClick: React.PropTypes.func.isRequired,
    stepNumber: React.PropTypes.number.isRequired
  };

  var DisclosableHeader = function DisclosableHeader(props) {
    // TODO: Actually DRY up the styles of this experiment succeeds.
    var headerClasses = classnames('focus-NotesView-RemindersList-remindersHeader', {
      'focus-NotesView-RemindersList-expanded': props.expanded
    });

    var onDismiss = function onDismiss(event) {
      props.onDismiss();
      event.stopPropagation();
    };

    var dismissButton = props.showDismiss && React.createElement('div', {
      className: 'FleChecklist-close',
      onClick: function onClick(e) {
        return onDismiss(e);
      },
      dangerouslySetInnerHTML: { __html: closeSvg }
    });

    return React.createElement(
      'div',
      {
        className: headerClasses,
        onClick: function onClick() {
          return props.onToggleHidden();
        }
      },
      React.createElement(
        'div',
        { className: 'focus-NotesView-RemindersList-remindersTitle' },
        i18n.L('Focus.fleChecklist.sectionHeader'),
        dismissButton
      )
    );
  };

  DisclosableHeader.propTypes = {
    expanded: React.PropTypes.bool.isRequired,
    onDismiss: React.PropTypes.func.isRequired,
    onToggleHidden: React.PropTypes.func.isRequired,
    showDismiss: React.PropTypes.bool.isRequired
  };

  /**
   * A checklist that users can interact with to learn more about the webclient
   * and Evernote.
   */

  var FleChecklist = function (_React$Component) {
    _inherits(FleChecklist, _React$Component);

    function FleChecklist(props) {
      _classCallCheck(this, FleChecklist);

      var _this = _possibleConstructorReturn(this, (FleChecklist.__proto__ || Object.getPrototypeOf(FleChecklist)).call(this, props));

      _this.state = {
        minimized: false
      };
      return _this;
    }

    _createClass(FleChecklist, [{
      key: 'componentDidMount',
      value: function componentDidMount() {
        this.reportHeight();
      }
    }, {
      key: 'componentDidUpdate',
      value: function componentDidUpdate() {
        this.reportHeight();
      }
    }, {
      key: 'reportHeight',
      value: function reportHeight() {
        var node = ReactDOM.findDOMNode(this);
        if (node) {
          this.props.onHeightUpdated(node.offsetHeight);
        }
      }
    }, {
      key: 'toggleHidden',
      value: function toggleHidden() {
        var minimized = !this.state.minimized;
        if (minimized) {
          this.props.onMinimize();
        } else {
          this.props.onExpand();
        }
        this.setState({ minimized: minimized });
      }
    }, {
      key: 'getDisclosableHeader',
      value: function getDisclosableHeader() {
        var _this2 = this;

        return React.createElement(DisclosableHeader, {
          expanded: !this.state.minimized,
          onDismiss: function onDismiss() {
            return _this2.props.onDismiss();
          },
          onToggleHidden: function onToggleHidden() {
            return _this2.toggleHidden();
          },
          showDismiss: this.getNumStepsDone() > 0
        });
      }
    }, {
      key: 'getNumStepsDone',
      value: function getNumStepsDone() {
        var boolToNum = function boolToNum(bool) {
          return bool ? 1 : 0;
        };
        return boolToNum(this.props.noteStepDone) + boolToNum(this.props.remindersStepDone) + boolToNum(this.props.clipperStepDone) + boolToNum(this.props.nativeStepDone);
      }
    }, {
      key: 'isCopyV2',
      value: function isCopyV2() {
        return this.props.variant === 'C' || this.props.variant === 'E';
      }
    }, {
      key: 'getMinimizedMessage',
      value: function getMinimizedMessage() {
        var baseKey = 'Focus.fleChecklist.minimized.upNext';
        if (!this.props.noteStepDone) {
          return i18n.L(baseKey, [i18n.L('Focus.fleChecklist.step.note.header')]);
        } else if (!this.props.remindersStepDone) {
          return i18n.L(baseKey, [i18n.L('Focus.fleChecklist.step.reminders.header')]);
        } else if (!this.props.clipperStepDone) {
          return i18n.L(baseKey, [i18n.L('Focus.fleChecklist.step.clipper.header')]);
        } else if (!this.props.nativeStepDone) {
          return i18n.L(baseKey, [i18n.L('Focus.fleChecklist.step.native.header')]);
        } else {
          // Everything is done - success!
          return i18n.L('Focus.fleChecklist.minimized.complete');
        }
      }
    }, {
      key: 'getHeaderMessage',
      value: function getHeaderMessage() {
        if (this.getNumStepsDone() >= TOTAL_STEPS) {
          return i18n.L('Focus.fleChecklist.header.complete');
        } else {
          return i18n.L('Focus.fleChecklist.header');
        }
      }
    }, {
      key: 'getDescriptionMessage',
      value: function getDescriptionMessage() {
        if (this.getNumStepsDone() >= TOTAL_STEPS) {
          return i18n.L('Focus.fleChecklist.description.complete');
        } else {
          return i18n.L('Focus.fleChecklist.description');
        }
      }
    }, {
      key: 'render',
      value: function render() {
        var meter = React.createElement(Meter, { numFilled: this.getNumStepsDone(), total: TOTAL_STEPS });

        if (this.state.minimized) {
          return React.createElement(
            'div',
            { className: 'FleChecklist-root' },
            this.getDisclosableHeader(),
            React.createElement(
              'h3',
              null,
              this.getMinimizedMessage()
            ),
            meter
          );
        } else {
          return React.createElement(
            'div',
            { className: 'FleChecklist-root' },
            this.getDisclosableHeader(),
            React.createElement(
              'h1',
              null,
              this.getHeaderMessage()
            ),
            React.createElement(
              'p',
              { className: 'FleChecklist-description' },
              this.getDescriptionMessage()
            ),
            meter,
            React.createElement(ChecklistItem, {
              complete: this.props.noteStepDone,
              description: i18n.L('Focus.fleChecklist.step.note.description'),
              header: i18n.L('Focus.fleChecklist.step.note.header'),
              onClick: this.props.onNoteStepClick,
              stepNumber: 1
            }),
            React.createElement(ChecklistItem, {
              complete: this.props.remindersStepDone,
              description: i18n.L('Focus.fleChecklist.step.reminders.description'),
              header: i18n.L('Focus.fleChecklist.step.reminders.header'),
              onClick: this.props.onRemindersStepClick,
              stepNumber: 2
            }),
            React.createElement(ChecklistItem, {
              complete: this.props.clipperStepDone,
              description: i18n.L('Focus.fleChecklist.step.clipper.description'),
              header: i18n.L('Focus.fleChecklist.step.clipper.header'),
              onClick: this.props.onClipperStepClick,
              stepNumber: 3
            }),
            React.createElement(ChecklistItem, {
              complete: this.props.nativeStepDone,
              description: i18n.L('Focus.fleChecklist.step.native.description'),
              header: i18n.L('Focus.fleChecklist.step.native.header'),
              onClick: this.props.onNativeStepClick,
              stepNumber: 4
            })
          );
        }
      }
    }]);

    return FleChecklist;
  }(React.Component);

  FleChecklist.propTypes = {
    clipperStepDone: React.PropTypes.bool.isRequired,
    nativeStepDone: React.PropTypes.bool.isRequired,
    noteStepDone: React.PropTypes.bool.isRequired,
    onClipperStepClick: React.PropTypes.func.isRequired,
    onDismiss: React.PropTypes.func.isRequired,
    onExpand: React.PropTypes.func.isRequired,
    onHeightUpdated: React.PropTypes.func.isRequired,
    onMinimize: React.PropTypes.func.isRequired,
    onNativeStepClick: React.PropTypes.func.isRequired,
    onNoteStepClick: React.PropTypes.func.isRequired,
    onRemindersStepClick: React.PropTypes.func.isRequired,
    remindersStepDone: React.PropTypes.bool.isRequired
  };

  return FleChecklist;
});