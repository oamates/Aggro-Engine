#include "TransformWidget.hpp"

TransformWidget::TransformWidget(QWidget *parent)
	: InspectorSubWidget(parent)
	, m_transXEdit(shared_ptr<QLineEdit>(new QLineEdit("")))
	, m_transYEdit(shared_ptr<QLineEdit>(new QLineEdit("")))
	, m_transZEdit(shared_ptr<QLineEdit>(new QLineEdit("")))
	, m_resetRotate(shared_ptr<QPushButton>(new QPushButton("Reset")))
	, m_scaleXEdit(shared_ptr<QLineEdit>(new QLineEdit("")))
	, m_scaleYEdit(shared_ptr<QLineEdit>(new QLineEdit("")))
	, m_scaleZEdit(shared_ptr<QLineEdit>(new QLineEdit("")))
{
	QHBoxLayout *mainLayout = new QHBoxLayout;
		QVBoxLayout *leftLayout = new QVBoxLayout;
		QVBoxLayout *rightLayout = new QVBoxLayout;
			QHBoxLayout *translateLayout = new QHBoxLayout;
			QHBoxLayout *rotateLayout = new QHBoxLayout;
			QHBoxLayout *scaleLayout = new QHBoxLayout;

	m_transXEdit->setFixedWidth(70);
	m_transYEdit->setFixedWidth(70);
	m_transZEdit->setFixedWidth(70);
	m_scaleXEdit->setFixedWidth(70);
	m_scaleYEdit->setFixedWidth(70);
	m_scaleZEdit->setFixedWidth(70);

	QLabel *lbl;

	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);

	leftLayout->addWidget(new QLabel("Position"));
	leftLayout->addWidget(new QLabel("Rotate"));
	leftLayout->addWidget(new QLabel("Scale"));

	rightLayout->addLayout(translateLayout);
	rightLayout->addLayout(rotateLayout);
	rightLayout->addLayout(scaleLayout);
	
	// Position
	lbl = new QLabel("X");
	lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	translateLayout->addWidget(lbl);
	translateLayout->addWidget(m_transXEdit.get());
	lbl = new QLabel("Y");
	lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	translateLayout->addWidget(lbl);
	translateLayout->addWidget(m_transYEdit.get());
	lbl = new QLabel("Z");
	lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	translateLayout->addWidget(lbl);
	translateLayout->addWidget(m_transZEdit.get());

	// Rotate
	m_resetRotate->setFixedHeight(30);
	m_resetRotate->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	//rotateLayout->addStretch();
	rotateLayout->addWidget(m_resetRotate.get());

	// Scale
	lbl = new QLabel("X");
	lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	scaleLayout->addWidget(lbl);
	scaleLayout->addWidget(m_scaleXEdit.get());
	lbl = new QLabel("Y");
	lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	scaleLayout->addWidget(lbl);
	scaleLayout->addWidget(m_scaleYEdit.get());
	lbl = new QLabel("Z");
	lbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	scaleLayout->addWidget(lbl);
	scaleLayout->addWidget(m_scaleZEdit.get());

	lbl = new QLabel("Transform");
	lbl->setStyleSheet("font-weight: bold; font-size: 16px;");
	m_layout->addWidget(lbl);
	m_layout->addLayout(mainLayout);

	connect(m_transXEdit.get(), &QLineEdit::textEdited, this, &TransformWidget::_onTransformChange);
	connect(m_transYEdit.get(), &QLineEdit::textEdited, this, &TransformWidget::_onTransformChange);
	connect(m_transZEdit.get(), &QLineEdit::textEdited, this, &TransformWidget::_onTransformChange);
	connect(m_scaleXEdit.get(), &QLineEdit::textEdited, this, &TransformWidget::_onTransformChange);
	connect(m_scaleYEdit.get(), &QLineEdit::textEdited, this, &TransformWidget::_onTransformChange);
	connect(m_scaleZEdit.get(), &QLineEdit::textEdited, this, &TransformWidget::_onTransformChange);
	connect(m_resetRotate.get(), &QPushButton::clicked, this, &TransformWidget::_onRotateReset);
}

void TransformWidget::_onTransformChange(QString newValue)
{
	if (m_currentNode && m_currentNode->getObject() && m_currentNode->getObject()->getTransformComponent())
	{
		shared_ptr<TransformComponent> transform = m_currentNode->getObject()->getTransformComponent();
		transform->removeChangeListener(this);
		transform->setTranslate(glm::vec3(
			m_transXEdit->text().toFloat(),
			m_transYEdit->text().toFloat(),
			m_transZEdit->text().toFloat()
		));
		transform->setScale(glm::vec3(
			m_scaleXEdit->text().toFloat(),
			m_scaleYEdit->text().toFloat(),
			m_scaleZEdit->text().toFloat()
		));
		transform->addChangeListener(this, [this](auto transform) {this->_refresh(transform);});
	}
}

void TransformWidget::_onRotateReset()
{
	if (m_currentNode && m_currentNode->getObject() && m_currentNode->getObject()->getTransformComponent())
	{
		shared_ptr<TransformComponent> transform = m_currentNode->getObject()->getTransformComponent();
		transform->setRotate(glm::mat4(1.0));
	}
}

void TransformWidget::_refresh(SceneNode *newNode)
{
	if (!newNode->getObject() || !newNode->getObject()->getTransformComponent())
	{
		this->hide();
		return;
	}

	shared_ptr<TransformComponent> transform = newNode->getObject()->getTransformComponent();
	_refresh(transform.get());

	if (m_lastActiveNode && m_lastActiveNode.get() != newNode)
	{
		if (m_lastActiveNode->getObject() && m_lastActiveNode->getObject()->getTransformComponent())
		{
			shared_ptr<TransformComponent> lastTransform = m_lastActiveNode->getObject()->getTransformComponent();
			lastTransform->removeChangeListener(this);
		}
	}

	if (!m_lastActiveNode || m_lastActiveNode.get() != newNode)
	{
		transform->addChangeListener(this, [this](auto transform) {this->_refresh(transform);});
	}
}

void TransformWidget::_refresh(TransformComponent *transform)
{
	m_transXEdit->setText(QString::number(transform->getTranslate()->x));
	m_transYEdit->setText(QString::number(transform->getTranslate()->y));
	m_transZEdit->setText(QString::number(transform->getTranslate()->z));
	m_scaleXEdit->setText(QString::number(transform->getScale()->x));
	m_scaleYEdit->setText(QString::number(transform->getScale()->y));
	m_scaleZEdit->setText(QString::number(transform->getScale()->z));
}